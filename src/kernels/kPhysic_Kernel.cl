typedef struct TransformComponent {
    float4 position;
    float4 eulers;
    float4 scale;
} TransformComponent;

typedef struct PhysicsComponent {
    float4 velocity;
    float4 acceleration;
    float mass;
    float radius;
    float pad1;
    float pad2;
} PhysicsComponent;

kernel void motion_kernel(global TransformComponent * TransformComponents,
                          global PhysicsComponent * PhysicsComponents,
                          const float dt, const int numEntities) {
    
    int id = get_global_id(0);
    if (id >= numEntities) return;

    PhysicsComponents[id].velocity[0] += PhysicsComponents[id].acceleration[0]*dt;
    PhysicsComponents[id].velocity[1] += PhysicsComponents[id].acceleration[1]*dt;
    PhysicsComponents[id].velocity[2] += PhysicsComponents[id].acceleration[2]*dt;

    TransformComponents[id].position[0] += PhysicsComponents[id].velocity[0]*dt;
    TransformComponents[id].position[1] += PhysicsComponents[id].velocity[1]*dt;
    TransformComponents[id].position[2] += PhysicsComponents[id].velocity[2]*dt;
}

kernel void gravity_kernel(global TransformComponent * TransformComponents,
                            global PhysicsComponent * PhysicsComponents,
                            const float G,
                            const int numEntities) {
    
    int id = get_global_id(0);
    if (id >= numEntities) return;
    float3 posA = TransformComponents[id].position.xyz;
    float3 acc = (float3)(0.0f, 0.0f, 0.0f);
    
    for (int j = 0; j < numEntities; j++) {
        float3 posB = TransformComponents[j].position.xyz;
        float3 dir = posB - posA;
        float distSqr = dot(dir, dir) + 1e-2f; // Avoid division by zero
        float dist = sqrt(distSqr);
        float forceMag = G * PhysicsComponents[id].mass * PhysicsComponents[j].mass / distSqr;

        float3 force = (forceMag / dist) * dir;
        acc += force / PhysicsComponents[id].mass;
    }
    
    PhysicsComponents[id].acceleration[0] = acc[0];
    PhysicsComponents[id].acceleration[1] = acc[1];
    PhysicsComponents[id].acceleration[2] = acc[2];
}

kernel void collision_kernel(global TransformComponent * TransformComponents,
                            global PhysicsComponent * PhysicsComponents,
                            const int numEntities) {
    int id = get_global_id(0);
    if (id >= numEntities) return;
    float3 posA = TransformComponents[id].position.xyz;
    float radiusA = PhysicsComponents[id].radius;
    float massA = PhysicsComponents[id].mass;
    float3 velA = PhysicsComponents[id].velocity.xyz;

    for (int j = id + 1; j < numEntities; j++) {
        float3 posB = TransformComponents[j].position.xyz;
        float radiusB = PhysicsComponents[j].radius;
        float massB = PhysicsComponents[j].mass;
        float3 velB = PhysicsComponents[j].velocity.xyz;

        float3 dir = posB - posA;
        float dist = length(dir);
        
        if (dist < (radiusA + radiusB)) {
            // Simple elastic collision response
            float3 normal = dir / dist;
            float3 tangent = (float3)(-normal.y, normal.x, normal.z);

            float vA_n = dot(velA, normal);
            float vA_t = dot(velA, tangent);
            float vB_n = dot(velB, normal);
            float vB_t = dot(velB, tangent);

            float vA_n_after = (vA_n * (massA - massB) + 2.0f * massB * vB_n) / (massA + massB);
            float vB_n_after = (vB_n * (massB - massA) + 2.0f * massA * vA_n) / (massA + massB);

            float vA_t_after = vA_t;
            float vB_t_after = vB_t;

            velA = vA_n_after * normal + vA_t_after * tangent;
            velB = vB_n_after * normal + vB_t_after * tangent;

            PhysicsComponents[id].velocity = (float4)(velA[0], velA[1], velA[2], 0.0f);
            PhysicsComponents[j].velocity = (float4)(velB[0], velB[1], velB[2], 0.0f);
        }
    }
}