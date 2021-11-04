import pygame as pg
import random

screen_width = 1280
screen_height = 720
resolution = [screen_width, screen_height]
background_color = (255, 255, 255)
red = (200, 0, 0)

screen = pg.display.set_mode(resolution)
pg.display.set_caption('Euler\'s disks')
screen.fill(background_color)

pg.display.flip()
printing = True


# Euler's disks
class Circles:
    def __init__(self, circle_x, circle_y, radius, border):
        self.circle_x = circle_x
        self.circle_y = circle_y
        self.radius = radius
        self.border = border

    def draw(self):
        pg.draw.circle(screen, red, (self.circle_x, self.circle_y), self.radius, self.border)


# create list with random position x and y of circles
position = [[], []]
for i in range(0, 100):
    pos_x = random.randint(0, screen_width)
    pos_y = random.randint(100, 600)
    position[0].append(pos_x)
    position[1].append(pos_y)

print(position)

# list comprehension
# creating circle objects
circles_list = [Circles(position[0][x], position[1][x], 20, 5) for x in range(0, 100)]

running = True
while running:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            running = False

    for i in range(len(circles_list)):
        circles_list[i].draw()

    pg.display.update()
