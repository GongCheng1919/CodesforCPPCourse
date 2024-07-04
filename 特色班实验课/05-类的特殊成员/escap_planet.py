class Universe:
    def __init__(self, gravitational_constant):
        self.gravitational_constant = gravitational_constant

class Planet:
    def __init__(self, universe, mass, radius):
        self.universe = universe
        self.mass = mass
        self.radius = radius

class Spaceship:
    def __init__(self, planet, acceleration, max_speed):
        self.planet = planet
        self.acceleration = acceleration
        self.max_speed = max_speed

    def escape_time(self):
        escape_speed = (2 * self.planet.universe.gravitational_constant * self.planet.mass / self.planet.radius) ** 0.5
        time_to_max_speed = self.max_speed / self.acceleration
        time_to_escape_speed = escape_speed / self.acceleration
        print("escape_speed=%.4g, time_to_max_speed=%.4g, time_to_escape_speed=%.4g"%(escape_speed, time_to_max_speed, time_to_escape_speed))
        if self.max_speed >= escape_speed:
            return time_to_escape_speed
        else:
            return None


def main():
    gravitational_constant = float(input())
    mass1, radius1, mass2, radius2, collision_t = map(float, input().split())
    universe = Universe(gravitational_constant)
    xenon = Planet(universe, mass1, radius1)
    folcon = Planet(universe, mass2, radius2)
    # collision_t = collision_time(universe, xenon, folcon, initial_distance)
    n = int(input())
    spaceships = []
    for _ in range(n):
        acceleration, max_speed = map(float, input().split())
        spaceship = Spaceship(xenon, acceleration, max_speed)
        spaceships.append(spaceship)
    successful_spaceships = [spaceship for spaceship in spaceships if spaceship.escape_time() is not None and spaceship.escape_time() <= collision_t]
    print(len(successful_spaceships))
    for spaceship in successful_spaceships:
        # print(min(spaceship.escape_time() * spaceship.max_speed, collision_t * spaceship.max_speed))
        time_to_max_speed = spaceship.max_speed / spaceship.acceleration
        distance = 0
        if time_to_max_speed>=collision_t:
            distance += 0.5*spaceship.acceleration*collision_t**2
        else:
            distance += 0.5*spaceship.acceleration*time_to_max_speed**2
            distance += (collision_t-time_to_max_speed)*spaceship.max_speed
        # distance = 0.5*spaceship.acceleration*time_to_max_speed**2+(collision_t-time_to_max_speed)*spaceship.max_speed
        print("{:.6g}".format(distance))

if __name__ == "__main__":
    main()
