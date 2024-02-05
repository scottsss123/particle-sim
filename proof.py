import pygame
import random
import time
import math

(WIDTH, HEIGHT) = (400, 400)
scl = 10
res = math.floor(WIDTH / scl)
window = pygame.display.set_mode((WIDTH, HEIGHT))

RIGHT_MOUSE = 3
LEFT_MOUSE = 1

elements = [False, False, False, False, False]

cell_types = {
    "sand": (240, 230, 140),
    "water": (0, 191, 255),
    "steam": (200, 200, 200),
    "wall": (100, 100, 100),
    "lava": (255, 102, 0),
    "empty": (0, 0, 0)
}


class Cell:
    Pos = []
    Colour = 0
    Type = ""

    def __init__(self, p, t):
        self.Pos = p
        self.Type = t
        self.Colour = cell_types[t]


def clamp(num, min_n, max_n):
    return max(min(max_n, num), min_n)


def empty_grid():
    empty_grid = []
    for i in range(res):

        row = []
        for j in range(res):
            row.append(Cell([j, i], "empty"))
        empty_grid.append(row)

    return empty_grid


def display_grid():
    window.fill((0, 0, 0))
    for row in grid:
        for cell in row:
            if cell.Type == "empty":
                continue
            pygame.draw.rect(window, cell.Colour, pygame.Rect(cell.Pos[0] * scl, cell.Pos[1] * scl, scl, scl))
    pygame.display.flip()


def update_grid():
    global grid, res, next_grid
    next_grid = empty_grid()

    for row in grid:
        for cell in row:
            ran_dir = random.choice([1, -1])

            x = cell.Pos[0]
            y = cell.Pos[1]

            if cell.Type == "empty":
                continue

            if cell.Type == "wall":
                next_grid[y][x] = cell
                continue

            if cell.Type == "steam":
                if y - 1 < 0:
                    next_grid[y][x] = cell
                    continue

                if grid[y - 1][x].Type == "empty":
                    cell.Pos[1] -= 1
                    next_grid[y - 1][x] = cell
                    continue

                if 0 < x + ran_dir < res:

                    if grid[y - 1][x + ran_dir].Type == "empty":
                        cell.Pos[0] += ran_dir
                        cell.Pos[1] -= 1
                        next_grid[y - 1][x + ran_dir] = cell
                        continue

                elif 0 < x - ran_dir < res:
                    if grid[y - 1][x - ran_dir].Type == "empty":
                        cell.Pos[0] -= ran_dir
                        cell.Pos[1] -= 1
                        next_grid[y - 1][x - ran_dir] = cell
                        continue

                if 0 < x + ran_dir < res:
                    if grid[y][x + ran_dir].Type == "empty":
                        cell.Pos[0] += ran_dir
                        grid[y][x + ran_dir] = cell
                elif 0 < x - ran_dir < res:
                    if grid[y][x - ran_dir].Type == "empty":
                        cell.Pos[0] -= ran_dir
                        grid[y][x - ran_dir] = cell

                next_grid[y][x] = cell
                continue

            if y + 1 >= res:
                next_grid[y][x] = cell
                continue

            if grid[y + 1][x].Type == "empty":
                cell.Pos[1] += 1
                next_grid[y + 1][x] = cell
                continue

            # lava + water => wall

            if 0 < x + ran_dir < res:
                if grid[y + 1][x + ran_dir].Type == "empty":
                    cell.Pos[0] += ran_dir
                    cell.Pos[1] += 1
                    next_grid[y + 1][x + ran_dir] = cell
                    continue
            elif 0 < x - ran_dir < res:
                if grid[y + 1][x - ran_dir].Type == "empty":
                    cell.Pos[0] -= ran_dir
                    cell.Pos[1] += 1
                    next_grid[y + 1][x - ran_dir] = cell
                    continue

            if cell.Type in ["water", "lava"]:
                if 0 < x + ran_dir < res:
                    if grid[y][x + ran_dir].Type == "empty":
                        cell.Pos[0] += ran_dir
                        grid[y][x + ran_dir] = cell
                elif 0 < x - ran_dir < res:
                    if grid[y][x - ran_dir].Type == "empty":
                        cell.Pos[0] -= ran_dir
                        grid[y][x - ran_dir] = cell

            next_grid[y][x] = cell

    grid = next_grid


grid = empty_grid()
next_grid = empty_grid()

running = 0
while running == 0:

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = -1
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_1:
                elements[0] = True
            if event.key == pygame.K_2:
                elements[1] = True
            if event.key == pygame.K_3:
                elements[2] = True
            if event.key == pygame.K_4:
                elements[3] = True
            if event.key == pygame.K_5:
                elements[4] = True
            if event.key == pygame.K_BACKSPACE:
                elements[-1] = True
        if event.type == pygame.KEYUP:
            if event.key == pygame.K_1:
                elements[0] = False
            if event.key == pygame.K_2:
                elements[1] = False
            if event.key == pygame.K_3:
                elements[2] = False
            if event.key == pygame.K_4:
                elements[3] = False
            if event.key == pygame.K_5:
                elements[4] = False
            if event.key == pygame.K_BACKSPACE:
                elements[-1] = False

    for element in range(len(elements)):
        if elements[element]:
            Type = list(cell_types.keys())[element]
            x, y = pygame.mouse.get_pos()
            x = clamp(math.floor(x / scl), 0, WIDTH - scl)
            y = clamp(math.floor(y / scl), 0, HEIGHT - scl)
            x = clamp(x, 0, (WIDTH // scl) - 1)
            y = clamp(y, 0, (HEIGHT // scl) - 1)
            grid[y][x] = Cell([x, y], Type) if grid[y][x].Type == "empty" else grid[y][x]
            if Type == "empty":
                grid[y][x] = Cell([x, y], Type) if grid[y][x].Type != "empty" else grid[y][x]

    display_grid()
    update_grid()

    time.sleep(0.01)
