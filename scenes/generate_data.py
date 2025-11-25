import numpy as np
import scipy
import matplotlib.pyplot as plt

'''
    Masa del sol: 1.989 x 10^30 kg
    Radio del sol: 696340 km

    Masa tierra: 5.972 x 10^24 kg
    Radio tierra: 6371 km
    Distancia tierra-sol: 1 UA

    Masa de Marte: 6.39 x 10^23 kg
    Radio de Marte: 3389.5 km
    Distancia marte-sol: 1.524 UA

    Masa de Jupiter: 1.898 x 10^27 kg
    Radio de Jupiter: 69911 km
    Distancia jupiter-sol: 5.204 AU

    Cantidad de asteroides en el cinturón principal: ~1.1 millones (diámetro > 1 km)
    distancia cinturon asteroidas: 2.7 AU - 3.3 AU
    desviacion estandar: 0.325 AU
    Rango de masas: 10^12 kg - 10^21 kg ~ lambda * exp(-x/lambda), lambda = 0.55 -> l(1-prob) + r*prob
    Densidades: 75% 1.3 x 10^6 kg/km^2, 15% 2.7 x 10^6 kg/km^2, 10% 5.0 x 10^6 kg/km^2
    Radio estimado: (m/2pi*rho)^(1/2)

    Gravitational constant: 6.67430 x 10^-11 m^2 kg^-1 s^-2
    velocidad orbital: v = sqrt(G * M / distance)

    1 UA = 1.496 x 10^11 m

    Scale factors:
    1 UA = 500 length units
    1 length unit = 2.992e8 m
    1 mass unit = 5.972e24 kg
    1 time unit = 86400 s

    G' = G * (mass_scale * time_scale^2) / length_scale^3
    G' = 6.67430e-11 * (5.972e24 * 86400^2) / (2.992e8)^3
'''
# Scale factors
length_scale = 2.992e8  # meters
mass_scale = 5.972e24   # kg
time_scale = 86400      # seconds
G_prime = 6.67430e-11 * (mass_scale * time_scale**2) / (length_scale**3)

def generate_asteroid_belt(num_asteroids: int, scale_factor: float = 2e1):
    positions = []
    masses = []
    velocities = []
    radius = []
    scale = []

    for _ in range(num_asteroids):
        # Generate distance from sun
        distance_au = np.random.normal(loc=3.0, scale=0.325)
        distance_ud = distance_au * 1.496e11 / length_scale  # convert to length units
        angle = np.random.uniform(0.0, 2 * np.pi)
        x = distance_ud * np.cos(angle)
        y = distance_ud * np.sin(angle)
        positions.append([x, y, 0.0])

        # Generate mass
        prob = np.random.exponential(scale=0.55)
        l = 1e12 / mass_scale  # in mass units
        r = 1e21 / mass_scale  # in mass units
        mass = l * (1 - prob) + r * prob
        masses.append(mass)

        # Determine density
        density_prob = np.random.rand()
        if density_prob < 0.75:
            density = 1.3e6  # kg/km^3
        elif density_prob < 0.90:
            density = 2.7e6  # kg/km^3
        else:
            density = 5.0e6  # kg/km^3

        density_unit = density / (mass_scale / (length_scale / 1000.0)**3)  # convert to mass units / (length units)^3

        # Calculate radius
        radius_ud = (3 * mass / (4.0 * np.pi * density_unit))**(1/3)
        radius.append(radius_ud)
        
        # Calculate orbital velocity
        M_sun = 1.989e30 / mass_scale # kg in mass units
        v_ud = np.sqrt(G_prime * M_sun / distance_ud)
        vx = -v_ud * np.sin(angle)
        vy = v_ud * np.cos(angle)
        velocities.append([vx, vy, 0.0])

        # Store scale
        scale.append(scale_factor)

    data = {'positions': np.array(positions), 'masses': np.array(masses),
            'velocities': np.array(velocities), 'radius': np.array(radius),
            'scale': np.array(scale)}
    return data

def add_sun(data, scale_factor: float = 1e1):
    sun_position = np.array([[0.0, 0.0, 0.0]])
    sun_mass = np.array([1.989e30 / mass_scale])  # in mass units
    sun_velocity = np.array([[0.0, 0.0, 0.0]])
    sun_radius = np.array([(696340.0) / (length_scale / 1000.0)])  # in length units

    data['positions'] = np.vstack((sun_position, data['positions']))
    data['masses'] = np.hstack((sun_mass, data['masses']))
    data['velocities'] = np.vstack((sun_velocity, data['velocities']))
    data['radius'] = np.hstack((sun_radius, data['radius']))
    data['scale'] = np.hstack((scale_factor, data['scale']))
    return data

def add_planet(data, distance_au, mass_kg, radius_km, scale_factor=1e2):
    distance_ud = distance_au * 1.496e11 / length_scale  # convert to length units
    angle = np.random.uniform(0.0, 2 * np.pi)
    x = distance_ud * np.cos(angle)
    y = distance_ud * np.sin(angle)
    position = np.array([[x, y, 0.0]])

    mass = np.array([mass_kg / mass_scale])  # in mass units

    v_ud = np.sqrt(G_prime * (1.989e30 / mass_scale) / distance_ud)
    vx = -v_ud * np.sin(angle)
    vy = v_ud * np.cos(angle)
    velocity = np.array([[vx, vy, 0.0]])

    radius_ud = radius_km / (length_scale / 1000.0)  # in length units
    radius = np.array([radius_ud])

    data['positions'] = np.vstack((data['positions'], position))
    data['masses'] = np.hstack((data['masses'], mass))
    data['velocities'] = np.vstack((data['velocities'], velocity))
    data['radius'] = np.hstack((data['radius'], radius))
    data['scale'] = np.hstack((data['scale'], scale_factor))
    return data

def main():
    N = 500 # Number of bodies
    data = generate_asteroid_belt(N)
    data = add_sun(data, scale_factor=2.3e1)
    data = add_planet(data, distance_au=1.0, mass_kg=5.972e24, radius_km=6371.0, scale_factor=7.5e2)  # Earth
    data = add_planet(data, distance_au=1.524, mass_kg=6.39e23, radius_km=3389.5, scale_factor=3.5e2)  # Mars
    data = add_planet(data, distance_au=5.204, mass_kg=1.898e27, radius_km=69911.0, scale_factor=1.5e2)  # Jupiter
    N += 4  # Update number of bodies

    # Save data to a .txt file
    np.savetxt('dataSet.txt', np.hstack((data['positions'], data['velocities'], data['masses'].reshape(-1, 1), data['radius'].reshape(-1, 1), data['scale'].reshape(-1, 1))),
               header=f'{N} {length_scale} {mass_scale} {time_scale} {G_prime}', comments='')

if __name__ == "__main__":
    main()