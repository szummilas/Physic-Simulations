import pygame
import random

pygame.init()
WIDTH = 1280
HEIGHT = 720
resolution = [WIDTH, HEIGHT]
BACKGROUND = pygame.image.load("background.jpg")
WHITE = (255, 255, 255)
PINK = (255, 63, 180)
LIME = (208, 255, 63)
BLUE = (99, 63, 255)
PURPLE = (103, 160, 237)

screen = pygame.display.set_mode(resolution)
pygame.display.set_caption('Euler\'s disks')

pygame.display.flip()
printing = True
TARGET_FPS = 30
clock = pygame.time.Clock()
gravity = 0.9
CENTER = pygame.math.Vector2(WIDTH / 2, HEIGHT / 2)

Dict = {
    1: 'gravity',
    2: 'attract',
    3: 'aerodynamics'
}


# Euler's disks
class Circle:
    def __init__(self):
        self.g = 0.9

        # random position
        self.position = pygame.math.Vector2(random.randint(0, WIDTH), random.randint(0, HEIGHT))

        # random velocity ( x axis and y axis )
        self.velocity = pygame.math.Vector2(random.randint(-39, 39) / 100, random.randint(-39, 39) / 100)

        # random drag
        self.drag = random.randint(970, 990) / 1000

        # force vector
        self.force = pygame.math.Vector2(0, 0)

    def update(self, mode, delta_time):
        if mode == 'gravity':
            # y = y + v * dt
            self.position = self.position + self.velocity * delta_time

            # v(y) = v(y) + g * dt
            self.velocity.y = self.velocity.y + self.g * delta_time
            self.velocity.x = 0.0

            # screen borders
            if self.position.y + self.velocity.y < 0 or self.position.y + self.velocity.y > HEIGHT:
                self.velocity.y = -self.velocity.y
            if self.position.x + self.velocity.x < 0 or self.position.x + self.velocity.x > HEIGHT:
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

    def draw(self, display, color):
        pygame.draw.circle(display, color, self.position, 4)


circles_list = [Circle() for _ in range(0, 1000)]
running = True
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
            if event.key == pygame.K_SPACE:
                circles_list.clear()
                circles_list = [Circle() for _ in range(0, 1000)]

    screen.blit(BACKGROUND, (0, 0))

    for i in range(len(circles_list)):
        circles_list[i].draw(screen, COLOR)
        circles_list[i].update(current_mode, dt)

    pygame.display.update()
