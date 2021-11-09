# TODO : clock

import pygame
import random

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
TARGET_FPS = 60
clock = pygame.time.Clock()
g = 9.81


# Euler's disks
class Circles:
    def __init__(self, number, radius, border, v):
        self.number = number
        self.radius = radius
        self.border = border
        self.v = v
        self.color = [random.randint(0, 255), random.randint(0, 255), random.randint(0, 255)]
        self.position = [random.randint(2 * self.radius, screen_width - 2 * self.radius),
                         random.randint(2 * self.radius, screen_height - 2 * self.radius)]

    def draw(self):
        pygame.draw.circle(screen, (self.color[0], self.color[1], self.color[2]), (self.position[0], self.position[1]),
                           self.radius, self.border)


# create list with random position x and y of circles
position = [[], []]
# for i in range(0, 1000):
#     pos_x = random.randint(0 + , screen_width)
#     pos_y = random.randint(100, 600)
#     position[0].append(pos_x)
#     position[1].append(pos_y)

# list comprehension
# creating circle objects
circles_list = [Circles(x, 10, 3, 3) for x in range(0, 1000)]

# y = y + v * dt
# v = v + g * dt

running = True
while running:
    dt = clock.tick(60) * .001 * TARGET_FPS
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    dt = clock.tick(30) / 1000.0

    screen.fill(background_color)

    for i in range(len(circles_list)):
        circles_list[i].draw()

        circles_list[i].v = circles_list[i].v + g * dt
        circles_list[i].position[1] = circles_list[i].position[1] + circles_list[i].v * dt

        if circles_list[i].position[0] > (screen_width - circles_list[i].radius):
            circles_list[i].v = - circles_list[i].v

        if circles_list[i].position[1] > (screen_height - circles_list[i].radius):
            circles_list[i].v = - circles_list[i].v

    pygame.display.update()