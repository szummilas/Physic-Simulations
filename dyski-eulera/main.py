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
    3: 'aerodynamics',
    4: 'point'
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
    def __init__(self):
        self.mass = 2
        self.g = 0.9
        self.gravity = 9.81

        # random position
        self.position = pygame.math.Vector2(random.randint(0, WIDTH), random.randint(0, HEIGHT))

        # random velocity ( x axis and y axis )
        self.velocity = pygame.math.Vector2(random.randint(-39, 39) / 100, random.randint(-39, 39) / 100)

        # random drag
        self.drag = random.randint(970, 990) / 1000

        # force vector
        self.force = pygame.math.Vector2(0, 0)

        # randomize
        self.random_color = [random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)]

    def update(self, mode, delta_time, size):
        if mode == 'gravity':
            # y = y + v * dt
            self.position = self.position + self.velocity * delta_time

            # v(y) = v(y) + g * dt
            self.velocity.y = self.velocity.y + self.g * delta_time

            # reset velocity in x axis
            self.velocity.x = 0.0

            # screen borders
            if self.position.y + self.velocity.y < 0 or self.position.y + self.velocity.y > HEIGHT:
                self.velocity.y = -self.velocity.y
            if self.position.x + self.velocity.x < 0 or self.position.x + self.velocity.x > WIDTH:
                self.velocity.x = -self.velocity.x

        elif mode == 'attract':
            # distance between cursor and disk position
            self.force = pygame.math.Vector2(pygame.mouse.get_pos()) - self.position
            self.force = self.force.normalize()

            # apply drag
            self.velocity *= self.drag

            # apply force
            self.velocity += self.force * 0.6

            # update position
            self.position += self.velocity

            # screen borders
            if self.position.x > WIDTH:
                self.position.x = WIDTH
                self.velocity.x *= -1.0
            elif self.position.x < 0:
                self.position.x = 0
                self.velocity.x *= -1.0

            if self.position.y > HEIGHT:
                self.position.y = HEIGHT
                self.velocity.y *= -1.0
            elif self.position.y < 0:
                self.position.y = 0
                self.velocity.y *= -1.0

        elif mode == 'aerodynamics':
            self.velocity.y += self.gravity * self.mass
            self.velocity += -6 * math.pi * 0.00001708 * size * self.velocity
            self.position += self.velocity

            # screen borders
            if self.position.y + self.velocity.y < 0 or self.position.y + self.velocity.y > HEIGHT:
                self.velocity.y = -self.velocity.y
            if self.position.x + self.velocity.x < 0 or self.position.x + self.velocity.x > WIDTH:
                self.velocity.x = -self.velocity.x

    def draw(self, display, color, size):
        pygame.draw.circle(display, color, self.position, size)


circles_list = [Circle() for _ in range(0, 1000)]
running = True
coloring = False
current_mode = Dict[1]
COLOR = PINK
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
                circles_list = [Circle() for _ in range(0, 1000)]

            if event.key == pygame.K_r:
                if not coloring:
                    coloring = True
                else:
                    coloring = False

        menu.react(event)

    screen.blit(BACKGROUND, (0, 0))

    for i in range(0, slider1.get_value()):
        if coloring:
            circles_list[i].draw(screen, circles_list[i].random_color, slider2.get_value())
        else:
            circles_list[i].draw(screen, COLOR, slider2.get_value())

        circles_list[i].update(current_mode, dt, slider2.get_value())

    box.blit()
    box.update()

    pygame.display.update()
