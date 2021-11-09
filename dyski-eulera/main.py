import pygame
import random
import thorpy

pygame.init()
screen_width = 1280
screen_height = 720
resolution = [screen_width, screen_height]
background_color = (255, 255, 255)
red = (200, 0, 0)

screen = pygame.display.set_mode(resolution)
pygame.display.set_caption('Euler\'s disks')
screen.fill(background_color)

pygame.display.flip()
printing = True
TARGET_FPS = 30
clock = pygame.time.Clock()
g = 0.9


# Euler's disks
class Circles:
    def __init__(self, number, radius, border):
        self.number = number
        self.radius = radius
        self.border = border
        self.velocity = pygame.math.Vector2(random.randint(1, 3), random.randint(1, 10))
        self.color = [random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)]
        self.position = pygame.math.Vector2(random.randint(2 * self.radius, screen_width - 2 * self.radius),
                                            random.randint(2 * self.radius, screen_height - 2 * self.radius))

    def physics(self, dt):
        # y = y + v * dt
        self.position = self.position + self.velocity * dt
        # v(y) = v(y) + g * dt
        self.velocity.y = self.velocity.y + g * dt

    def update(self, dt):
        self.physics(dt)

    def draw(self, display):
        pygame.draw.circle(display, self.color, self.position, self.radius, self.border)


# list comprehension
# creating circle objects
circles_list = [Circles(x, 10, 3) for x in range(0, 1000)]

# THOR.PY
slider_quantity = thorpy.SliderX(100, (0, 1000), "Quantity")
slider_size = thorpy.SliderX(100, (10, 50), "Size")
box = thorpy.Box(elements=[slider_quantity, slider_size])
menu = thorpy.Menu(box)
for element in menu.get_population():
    element.surface = screen
box.set_topleft((100, 100))


running = True
freeze_time = False
while running:
    dt = clock.tick(30) * .001 * TARGET_FPS
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_SPACE:
                if not freeze_time:
                    freeze_time = True
                else:
                    freeze_time = False

        menu.react(event)

    screen.fill(background_color)
    box.blit()
    box.update()

    for i in range(1, int(slider_quantity.get_value())):
        if not freeze_time:
            circles_list[i].update(dt)
        circles_list[i].draw(screen)

        circles_list[i].radius = int(slider_size.get_value())

        if circles_list[i].position.x >= (screen_width - circles_list[i].radius) or \
                circles_list[i].position.x <= 0 + circles_list[i].radius:
            circles_list[i].velocity.x = - circles_list[i].velocity.x

        if circles_list[i].position.y >= (screen_height - circles_list[i].radius):
            circles_list[i].velocity.y = - circles_list[i].velocity.y

    pygame.display.update()
