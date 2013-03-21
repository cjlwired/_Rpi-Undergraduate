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
def define(self,i,render):
	'''used for generating random positions and creating balls to be dropped'''
	t = random.randint(1,13)
	x=random.randint(10,196)
	z = random.randint(0,135)
	if t==1:
		self.append(Actor("models/gamedev/sawball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==2:
		self.append(Actor("models/gamedev/moltovball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==3:
		self.append(Actor("models/gamedev/grenadeball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==4:
		self.append(Actor("models/gamedev/death"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-25)
		self[i].setPos(Vec3(x,0,z))
	elif t==5:
		self.append(Actor("models/gamedev/pogo"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==6:
		self.append(Actor("models/gamedev/golden"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==7:
		self.append(Actor("models/gamedev/greenball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==8:
		self.append(Actor("models/gamedev/crystalball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==9:
		self.append(Actor("models/gamedev/fireball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==10:
		self.append(Actor("models/gamedev/translucent"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==11:
		self.append(Actor("models/gamedev/blackball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	elif t==12:
		self.append(Actor("models/gamedev/question"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-15)
		self[i].setPos(Vec3(x,0,z))
	else:
		self.append(Actor("models/gamedev/superball"))
		self[i].reparentTo(render)
		self[i].setScale(3)
		self[i].setH(-25)
		self[i].setPos(Vec3(x,0,z))