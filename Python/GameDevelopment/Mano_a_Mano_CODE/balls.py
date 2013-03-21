import direct.directbase.DirectStart
from pandac.PandaModules import *
from direct.showbase.DirectObject import DirectObject
from direct.actor.Actor import Actor
from direct.interval.IntervalGlobal import *
from direct.task import Task
import sys
import math #trig function and pi!
import random


#constructor
def define(self,i,render,center,radius):
	'''used for generating random positions and creating balls to be dropped'''
	x = random.randint(0,100)
	z = random.randint(0,1)
	if z == 0:
		z = -1
	
	xpos = random.random()*radius*z
	
	z = random.randint(0,1)
	if z == 0:
		z = -1
	ypos = random.random()*radius*z
	
	if x < 40:
		self.append(Actor("models/gamedev/blueball"))
		self[i].reparentTo(render)
		self[i].setScale(.3)
		self[i].setH(0)
		self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
	elif x < 80:
		self.append(Actor("models/gamedev/redball"))
		self[i].reparentTo(render)
		self[i].setScale(.3)
		self[i].setH(0)
		self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
	else:
		t = random.randint(1,9)
		if t==1:
			self.append(Actor("models/gamedev/crystalball"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
		elif t==2:
			self.append(Actor("models/gamedev/fireball"))
			self[i].reparentTo(render)
			self[i].setScale(.2)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
		elif t==3:
			self.append(Actor("models/gamedev/greenball"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
		elif t==4:
			self.append(Actor("models/gamedev/golden"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+49.7))
		elif t==5:
			self.append(Actor("models/gamedev/redblue"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+49.7))
		elif t==6:
			self.append(Actor("models/gamedev/blackball"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
		elif t==7:
			self.append(Actor("models/gamedev/translucent"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+50))
		elif t==8:
			self.append(Actor("models/gamedev/question"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+49.7))
			type = random.randint(0,7)
			if type == 0:
				self[i].setName("crystalball")
			elif type == 1:
				self[i].setName("fireball")
			elif type == 2:
				self[i].setName("greenball")
			elif type == 3:
				self[i].setName("golden")
			elif type == 4:
				self[i].setName("redblue")
			elif type == 5:
				self[i].setName("blackball")
			elif type == 6:
				self[i].setName("translucent")
			else:
				self[i].setName("blackwhite")
		else:
			self.append(Actor("models/gamedev/blackwhite"))
			self[i].reparentTo(render)
			self[i].setScale(.3)
			self[i].setH(0)
			self[i].setPos(Vec3(center.getX()+xpos,center.getY()+ypos,self[i].getZ()+49.7))