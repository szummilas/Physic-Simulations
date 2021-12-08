import math

from config import *

screen = pygame.display.set_mode([WIDTH, HEIGHT])
pygame.display.set_caption('Euler\'s disks')
pygame.init()
pygame.display.flip()
clock = pygame.time.Clock()

Dict = {
    1: 'gravity',
    2: 'attract',
    3: 'point'
}

slider1 = thorpy.SliderX(100, (1, 1000), "ELEMENTS", type_=int, initial_value=100)
slider1.set_font_color(WHITE)
slider2 = thorpy.SliderX(120, (1, 10), "SIZE", type_=int)
slider2.set_font_color(WHITE)
box = thorpy.Box(elements=[slider1, slider2])
menu = thorpy.Menu(box)

for element in menu.get_population():
    element.surface = screen

box.set_topleft((0, 0))
box.set_main_color((255, 255, 255, 100))


# Euler's disks
class Circle:
    def __init__(self, size):
        self.g = 0.9
        self.gravity = 9.81
        self.grav = 0
        self.r = 0
        self.f_vec = pygame.math.Vector2(0, 0)
        self.f = 0

        # random position
        self.position = pygame.math.Vector2(random.randint(0 + size, WIDTH - size),
                                            random.randint(0 + size, HEIGHT - size))

        # random velocity ( x axis and y axis )
        self.velocity = pygame.math.Vector2(random.randint(-39, 39) / 1000, random.randint(-39, 39) / 1000)

        # random drag
        self.drag = random.randint(970, 990) / 1000

        # force vector
        self.force = pygame.math.Vector2(0, 0)

        # randomize
        self.random_color = [random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)]

        # init acceleration
        self.acceleration = pygame.math.Vector2(0, 0)

        # random mass
        self.mass = random.randint(20, 200)

    def update(self, mode, delta_time, size):
        if mode == 'gravity':
            # y = y + v * dt
            self.position.y += self.velocity.y * delta_time + 1/2 * self.gravity * delta_time**2
            self.position.x += self.velocity.x

            # v(y) = v(y) + g * dt
            self.velocity.y += self.g * delta_time

        elif mode == 'attract':
            # vector of mouse position
            # mouse_pos = pygame.math.Vector2(pygame.mouse.get_pos())
            # r^2 = (x_2-x1)^2 + (y_2 - y1)^2
            # r = (mouse_pos.x - self.position.x)**2 + (mouse_pos.y - self.position.y)**2
            # F = G * m * M / r^2
            # self.grav = 6.67 * 10e-11 * self.mass * other_mass / r
            # result vector of gravity force
            self.force = pygame.math.Vector2(pygame.mouse.get_pos()) - self.position
            self.force = self.force.normalize()

            # apply drag
            self.velocity *= self.drag

            # apply force
            self.velocity += self.force * 0.6

            # update position
            self.position += self.velocity

        elif mode == 'point':
            # wektor w ktora strone ma byc sila
            self.force = CENTER - self.position
            # normalizacja czyli wersor
            self.force = self.force.normalize()

            # mianownik
            # r = sqrt((x1-x2)^2 + (y1-y2)^2)
            self.r = math.sqrt(pow(CENTER.x - self.position.x, 2) + pow(CENTER.y - self.position.y, 2))
            # sila grawitacji F = G * M * m / r ^ 2
            self.f = (self.mass * 1000) / (pow(self.r + size, 2))

            # nadanie wersorowi wartości siły F
            self.f_vec = self.f * self.force

            # przyspieszenie a = F / m
            self.acceleration += self.f_vec / self.mass

            if self.acceleration.x > 2 or self.acceleration.y > 2 or \
                    self.acceleration.x < -2 or self.acceleration.y < -2:
                self.acceleration.x = 0
                self.acceleration.y = 0

            if self.r > 300:
                self.r = -self.r

            # -a - sila oporu
            self.acceleration += -6 * math.pi * self.velocity * 0.00001 * size

            if self.velocity.x > 10 or self.velocity.x < -10:
                self.velocity.x = 0
            elif self.velocity.y > 10 or self.velocity.y < -10:
                self.velocity.y = 0

        self.velocity += self.acceleration * delta_time
        self.position += self.velocity * delta_time

        # screen borders
        if self.position.x >= WIDTH - size:
            self.position.x = WIDTH - size
            self.velocity.x *= -1.0
        elif self.position.x <= 0 + size:
            self.position.x = 0 + size
            self.velocity.x *= -1.0

        if self.position.y >= HEIGHT - size:
            self.position.y = HEIGHT - size
            self.velocity.y *= -1.0
        elif self.position.y <= 0 + size:
            self.position.y = 0 + size
            self.velocity.y *= -1.0

    def draw(self, display, color, size):
        pygame.draw.circle(display, color, self.position, size)


class Point:
    def __init__(self):
        self.position = pygame.math.Vector2(0, 0)
        self.size = 20
        self.color = WHITE

    def draw(self, display, position):
        pygame.draw.circle(display, self.color, position, self.size)


circles_list = [Circle(slider2.get_value()) for _ in range(0, 1000)]
points_list = []
points_pos_list = []
running = True
coloring = False
current_mode = Dict[1]
COLOR = PINK
big_mass = 1000
click = 0
while running:
    dt = clock.tick(TARGET_FPS) * .001 * TARGET_FPS
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:
                COLOR = PINK
                TARGET_FPS = 30
                current_mode = Dict[1]

            if event.key == pygame.K_2:
                COLOR = LIME
                TARGET_FPS = 60
                current_mode = Dict[2]

            if event.key == pygame.K_3:
                COLOR = BLUE
                TARGET_FPS = 30
                current_mode = Dict[3]

            if event.key == pygame.K_SPACE:
                circles_list.clear()
                circles_list = [Circle(slider2.get_value()) for _ in range(0, 1000)]

            if event.key == pygame.K_r:
                if not coloring:
                    coloring = True
                else:
                    coloring = False

        # if event.type == pygame.MOUSEBUTTONDOWN:
        #     if event.button == 1 and current_mode == 'point':
        #         mouse_pos = pygame.math.Vector2(pygame.mouse.get_pos())
        #         points_pos_list.append(mouse_pos)
        #         point = Point()
        #         points_list.append(point)

        menu.react(event)

    screen.blit(BACKGROUND, (0, 0))
    for i in range(len(points_list)):
        points_list[i].draw(screen, points_pos_list[i])

    for i in range(0, slider1.get_value()):
        # if circles_list[i].position.x < 20:
        #     print(f"vel: {circles_list[i].velocity}, acc: {circles_list[i].acceleration}, r: {circles_list[i].r}, f: {circles_list[i].f_vec}")
        # print(circles_list[i].f_vec)

        if coloring:
            circles_list[i].draw(screen, circles_list[i].random_color, slider2.get_value())
        else:
            circles_list[i].draw(screen, COLOR, slider2.get_value())

        if len(points_list) > 0:
            circles_list[i].update(current_mode, dt, slider2.get_value())
        else:
            circles_list[i].update(current_mode, dt, slider2.get_value())

    box.blit()
    box.update()

    pygame.display.update()
