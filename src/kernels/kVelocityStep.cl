typedef struct TransformComponent {
    float3 position;
    float3 eulers;
    float3 scale;
    float2 shearX;
    float2 shearY;
    float2 shearZ;
} TransformComponent;

typedef struct PhysicsComponent {
    float3 velocity;
    float3 acceleration;
    float mass;
    float radius;
} PhysicsComponent;

kernel void velocity_step(global TransformComponent * TransformComponents,
                          global PhysicsComponent * PhysicsComponents,
                          const float dt) {
    
    int id = get_global_id(0);
    PhysicsComponents[id].velocity[0] += PhysicsComponents[id].acceleration[0] * dt;
    PhysicsComponents[id].velocity[1] += PhysicsComponents[id].acceleration[1] * dt;
    PhysicsComponents[id].velocity[2] += PhysicsComponents[id].acceleration[2] * dt;
}