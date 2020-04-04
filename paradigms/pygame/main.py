# Nathan Vahrenberg
# CSE 30332 Programming Paradigms
# PyGame Primer
# 15 April 2016

import sys
import os
import time
import math
import pygame
from pygame.locals import *

class Player(pygame.sprite.Sprite):
	def __init__(self, gs=None):
		pygame.sprite.Sprite.__init__(self)

		self.angle = 0

		self.gs = gs
		self.image = pygame.image.load("resources/deathstar.png")
		self.rect = self.image.get_rect()
		self.orig_image = self.image

		self.laser_image = pygame.image.load("resources/laser.png")
		self.laser_orig = self.laser_image
		self.laser_rect = self.laser_image.get_rect()

		self.laser_sound = pygame.mixer.Sound("resources/screammachine.wav")

		self.hit = 0
		self.tofire = False
		self.dx = 0
		self.dy = 0

		self.speed = 1

	def tick(self):
		if self.tofire:
			self.laser_rect[0] += 5*math.cos(self.angle*3.14/90)
			self.laser_rect[1] += -5*math.sin(self.angle*3.14/90)
			self.laser_image = pygame.transform.rotate(self.laser_orig, self.angle)
			if self.laser_rect[0] > 500 and self.laser_rect[1] > 200:
				if self.hit == 0:
					self.hit = 1
					self.tofire = False
				elif self.hit == 1:
					self.hit = 2
					self.tofire = False
			if self.laser_rect[0] > 640 or self.laser_rect[0] < 0 or self.laser_rect[1] > 480 or self.laser_rect[1] < 0:
				self.tofire = False
		else:
			mx, my = pygame.mouse.get_pos()
			self.angle = 0 - math.atan2(my-self.rect[1], mx-self.rect[0])*(90/3.14)
			self.rect[0] += self.dx
			self.rect[1] += self.dy
			self.image = pygame.transform.rotate(self.orig_image, self.angle)

	def set_laser_pos(self):
		self.laser_rect[0] = self.rect[0] + 50
		self.laser_rect[1] = self.rect[1] + 50
		self.laser_sound.play()

	def move_x(self, x):
		self.dx = x * self.speed

	def move_y(self, y):
		self.dy = y * self.speed

class Planet(pygame.sprite.Sprite):
	def __init__(self, gs=None):
		pygame.sprite.Sprite.__init__(self)

		self.gs = gs
		self.image = pygame.image.load("resources/globe.png")
		self.image2 = pygame.image.load("resources/globe_red100.png")
		self.rect = self.image.get_rect()
		self.rect[0] = 500
		self.rect[1] = 200
		self.orig_image = self.image

	def tick(self):
		pass

	def hit(self):
		self.image = self.image2
		self.orig_image = self.image

class Explosion(pygame.sprite.Sprite):
	def __init__(self, gs=None):
		pygame.sprite.Sprite.__init__(self)

		self.image = pygame.image.load("resources/explosion/frames000a.png")
		self.rect = self.image.get_rect()
		self.rect[0] = 550
		self.rect[1] = 250

		self.sound = pygame.mixer.Sound("resources/explode.wav")

		self.gs = gs
		self.frame = 0
		self.delay = 3
		self.counter = 0

	def play_sound(self):
		self.sound.play()

	def animate(self):
		if self.counter < self.delay:
			pass
		else:
			self.counter = 0
			if self.frame < 10:
				self.image = pygame.image.load("resources/explosion/frames00" + str(self.frame) + "a.png")
			else:
				self.image = pygame.image.load("resources/explosion/frames0" + str(self.frame) + "a.png")
				self.rect = self.image.get_rect()
			self.rect[0] = 550
			self.rect[1] = 250
			self.frame += 1
		self.counter += 1

class GameSpace:
	def main(self):
		pygame.init()
		pygame.mixer.init()
		self.size = self.width, self.height = 640, 480
		self.black = 0, 0, 0
		self.screen = pygame.display.set_mode(self.size)

		self.clock = pygame.time.Clock()

		self.player = Player(self)

		self.planet = Planet(self)
		self.explosion = Explosion(self)

if __name__ == '__main__':

	gs = GameSpace()
	gs.main()

	gs.clock.tick(60)

	while True:

		if gs.player.hit == 1:
			gs.planet.hit()
		if gs.player.hit == 2:
			break

		for event in pygame.event.get():
			if event.type == QUIT:
				break
			elif event.type == KEYDOWN:
				if event.key == K_UP:
					gs.player.move_y(-1)
				if event.key == K_DOWN:
					gs.player.move_y(1)
				if event.key == K_LEFT:
					gs.player.move_x(-1)
				if event.key == K_RIGHT:
					gs.player.move_x(1)
				if event.key == K_SPACE:
					gs.player.set_laser_pos()
					gs.player.tofire = True
			elif event.type == KEYUP:
				if event.key == K_UP or event.key == K_DOWN:
					gs.player.move_y(0)
				if event.key == K_LEFT or event.key == K_RIGHT:
					gs.player.move_x(0)
			else:
				pass

		gs.player.tick()

		if gs.player.tofire:
			gs.screen.blit(gs.player.laser_image, gs.player.laser_rect)
		else:
			gs.screen.fill(gs.black)
		
		gs.screen.blit(gs.player.image, gs.player.rect)
		gs.screen.blit(gs.planet.image, gs.planet.rect)
		pygame.display.flip()

	gs.explosion.play_sound()

	for i in range(0, 53):
		gs.clock.tick(60)
		gs.explosion.animate()

		gs.screen.fill(gs.black)
		gs.screen.blit(gs.player.image, gs.player.rect)
		gs.screen.blit(gs.explosion.image, gs.explosion.rect)
		pygame.display.flip()

	time.sleep(2)