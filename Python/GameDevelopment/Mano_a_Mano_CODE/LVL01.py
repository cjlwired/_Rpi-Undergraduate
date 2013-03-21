import direct.directbase.DirectStart
from pandac.PandaModules import *
from direct.showbase.DirectObject import DirectObject
from direct.actor.Actor import Actor
from direct.interval.IntervalGlobal import *
from direct.task import Task
import sys
import math #trig function and pi!
import random
from direct.gui.OnscreenImage import OnscreenImage
from direct.gui.OnscreenText import OnscreenText 
from direct.gui.DirectGui import *

class Lvl01(DirectObject):
	#constructor
	def start(self):
		base.disableMouse() #turn off mouse camera control
		#camera.setPosHpr(Vec3(93,-90,0), Vec3(0,0,0))
		# Turn off the default camera and replace it with two new cameras, with 
		# side-by-side DisplayRegions. 
		
		base.camNode.setActive(0)
		base.makeCamera(base.win, displayRegion = (0, 0.48, 0, 1)) 
		base.makeCamera(base.win, displayRegion = (0.52, 1, 0, 1))
		base.makeCamera(base.win, displayRegion = (0.48,0.52,0,1))
	
		base.camList[3].setPos(Vec3(144,0,-1000))
		
		self.gameLen = 100
		
		self.numActuator = 10
		
		self.music = loader.loadMusic("models/gamedev/AD.mp3")
		self.music.play()
		
		globalClock.reset()
		self.timer = OnscreenText("%d" % (self.gameLen-globalClock.getRealTime(),), pos = (98,145), scale = 18.0)
		self.timer.setColor(1,1,1)
		taskMgr.add(self.clockTask,"clockTask")
	
		self.actCount = 0
		self.speed1 = 3
		self.speed2 = 3
		self.climbSpeed1 = 1
		self.climbSpeed2 = 1
		self.climbing1 = 0
		self.climbing2 = 0
	
                self.array = []
                
                self.loadModels()
                self.setupLighting()
                self.setupStage()
                self.setupCollisions()
                self.setupIntervals()
                
                self.player1Score = 0
                self.player2Score = 0
                  
                self.dir1 = 1
                self.dir2 = 1
                self.nodeCount1 = 0
		self.nodeCount2 = 0

		taskMgr.add(self.cameraFollowTask,"cameraFollowTask")
		taskMgr.add(self.boulderTask,"boulderTask")
		
		taskMgr.doMethodLater(self.gameLen,self.endGame,'endGame')

		#setup key controls
		self.accept("escape",sys.exit)
		#self.accept("w",self.rise)
		#self.accept("o",self.rise2)
	
		#Player 1 movement keys
	
		#self.accept("s",self.fall)
		
		self.acceptOnce("a",self.left)
		self.acceptOnce("d",self.right)
	
		self.accept("a-up",self.stopLeft)
		self.accept("d-up",self.stopRight)
	
		self.acceptOnce("w", self.jump)
		self.acceptOnce("o", self.jumpT2)
	
		#Player 2 movement keys
		#self.accept("l",self.fall2)
		
		self.acceptOnce("k",self.left2)
		self.acceptOnce(";",self.right2)
	
		self.accept("k-up",self.stopLeft2)
		self.accept(";-up",self.stopRight2)
	
		self.jumpOK = 1

	def loadModels(self):
		
		print "start loadModels"
		
		self.playerModel = Actor("models/gamedev/redguy-model",{"walk":"models/gamedev/redguyrun",
			"jump":"models/gamedev/redguy-jump","climb":"models/gamedev/redguy-climb"})
		self.playerModel.reparentTo(render)
		self.playerModel.setScale(.7)
		self.playerModel.setPosHpr(Vec3(46,0,0),Vec3(0,0,0))
		self.playerModel.setH(90)
	
	
		self.playerModel2 = Actor("models/gamedev/bluegirl-model",{"walk2":"models/gamedev/bluegirlrun",
			"jump2":"models/gamedev/bluegirl-jump","climb2":"models/gamedev/bluegirl-climb"})
		self.playerModel2.reparentTo(render)
		self.playerModel2.setScale(.7)
		self.playerModel2.setPosHpr(Vec3(333,0,0),Vec3(0,0,0))
		self.playerModel2.setH(270)

		self.divider = loader.loadModel("models/gamedev/divider")
		self.divider.setPos(144,0,-1000)
		self.divider.setScale(5.0)
		self.divider.reparentTo(render)
		
		self.boulder1 = loader.loadModel("models/gamedev/boulder")
		self.boulder1.reparentTo(render)
		self.boulder1.setScale(7)
		self.boulder1.setPos(46,0,-50)
		self.boulder2 = loader.loadModel("models/gamedev/boulder")
		self.boulder2.reparentTo(render)
		self.boulder2.setScale(7)
		self.boulder2.setPos(333,0,-50)
		
		#loader.loadModel("models/gamedev/actuatorOn")
		
		bounds = self.boulder1.getChild(0).getBounds()
		center = bounds.getCenter()
		radius = bounds.getRadius()*.7
		cSphere = CollisionSphere(center,radius)
		cNode = CollisionNode("boulder")
		cNode.addSolid(cSphere)
		cNodePath = self.boulder1.attachNewNode(cNode)
		#cNodePath.show()
		cNodePath = self.boulder2.attachNewNode(cNode)
		#cNodePath.show()
		
		print "end loadModels"

	def setupStage(self):
		
		print "start setupStage"
		
		self.background = OnscreenImage(image = 'models/gamedev/lvl1background.jpg', pos = (175,5,0),scale=500)
		self.background.reparentTo(render)
	
		x1= 4.9
		x2 = -4.9
		len = 9.8
		h = 0
		a = 0
		p = 0
		j=0
		m=0
		x1b=0
		x2b=0

		while self.actCount < self.numActuator:
			if j > 0:
				lOld = l
				rOld = r
				x1Old = x1
				x2Old = x2
				x1 = (x1Old+x2Old)/2 + 4.9
				x2 = (x1Old+x2Old)/2 - 4.9
				x1o=x1
				x2o=x2
				
				for count in range(1):
					l = random.randint(0,(10-lOld)+((10+rOld)-(10-lOld))/2)
					r = random.randint(0,20-((10-lOld)+((10+rOld)-(10-lOld))/2))
					if r+2 <= 20-((10-lOld)+((10+rOld)-(10-lOld))/2):
						r += 2
					if l+2 < (10-lOld)+((10+rOld)-(10-lOld))/2:
						l += 2
					if 	l+r < 4:
						count = 0
				p = random.randint(0,1)
			else:
				l = 10
				r = 10
				c = 10
			#while a == 0:
			a = random.randint(-l,r)
			if j > 0:
				if j % 2 == 0:
					self.ladder = loader.loadModel("models/gamedev/ladder")
					self.ladder.reparentTo(render)
					self.ladder.setScale(1.5)
					self.ladder.setPos(x1+m,0,h-20)
					self.ladder2 = loader.loadModel("models/gamedev/ladder")
					self.ladder2.reparentTo(render)
					self.ladder2.setScale(1.5)
					self.ladder2.setPos(x1+286+m,0,h-20)
                                        self.array.append(self.ladder)
                                        self.array.append(self.ladder2)
					
				else:
					self.ladder = loader.loadModel("models/gamedev/ladder")
					self.ladder.reparentTo(render)
					self.ladder.setScale(1.5)
					self.ladder.setPos(x2,0,h-20)
					self.ladder2 = loader.loadModel("models/gamedev/ladder")
					self.ladder2.reparentTo(render)
					self.ladder2.setScale(1.5)
					self.ladder2.setPos(x2+286,0,h-20)
                                        self.array.append(self.ladder)
                                        self.array.append(self.ladder2)
				k=-10
				while k <= 13:
					cSphere = CollisionSphere(Point3(1.5,0,k),.5)
					cNode = CollisionNode("ladder")
					cNode.addSolid(cSphere)
					cNodePath = self.ladder.attachNewNode(cNode)
					cNodePath = self.ladder2.attachNewNode(cNode)
					#cNodePath.show()
					k+=1
                                        self.array.append(self.ladder)
				
				#cSphere = CollisionSphere(Point3(1.5,0,h-40),.5)
				#cNodeB = CollisionNode("canWalk")
				#cNodeB.addSolid(cSphere)
				#cNodePath = self.ladder.attachNewNode(cNodeB)
				#cNodePath = self.ladder2.attachNewNode(cNodeB)
			for i in range(r):
				'''Right half of stage'''
				self.environment = loader.loadModel("models/gamedev/platform")
				self.environment.reparentTo(render)
				self.environment.setScale(5)
				self.environment.setPos(x1,0,h)
				self.environment2 = loader.loadModel("models/gamedev/platform")
				self.environment2.reparentTo(render)
				self.environment2.setScale(5)
				self.environment2.setPos(x1+286,0,h)
                                self.array.append(self.environment)
                                self.array.append(self.environment2)
				
				#if i == 0 and j > 0:
				#	cSphere = CollisionSphere(Point3((m/9.8)*1.9,0,0),.5)
				#	cNode = CollisionNode("platform")
				#	cNode.addSolid(cSphere)
				#	cNodePath = self.environment.attachNewNode(cNode)
				#	cNodePath = self.environment2.attachNewNode(cNode)
				#	cNodePath.show()
				
				if r == i+1:
					cSphere = CollisionSphere(Point3(2,0,0),2)
					if i == 9:
						cNode = CollisionNode("rwall")
					else:
						cNode = CollisionNode("redge")
					cNode.addSolid(cSphere)
					cNodePath = self.environment.attachNewNode(cNode)
					cNodePath = self.environment2.attachNewNode(cNode)
					#cNodePath.show()
				if a == i:
					self.actCount+=1
					self.actuator = Actor("models/gamedev/actuator")
					self.actuator.reparentTo(render)
					self.actuator.setPos(self.environment.getPos())
					if p == 1:
						self.actuator.setZ(self.actuator.getZ())
						self.actuator.setP(self.actuator.getP()+180)
					self.actuator.setScale(2)
					self.actuator.setH(self.actuator.getH()+180)
                                        self.array.append(self.actuator)
					bounds = self.actuator.getChild(0).getBounds()
					center = bounds.getCenter()
					radius = bounds.getRadius()-.5
					cSphere = CollisionSphere(center,radius)
					cNode = CollisionNode("actuator")
					cNode.addSolid(cSphere)
					cNodePath = self.actuator.attachNewNode(cNode)
					#cNodePath.show()
					
					self.actuator2 = Actor("models/gamedev/actuator")
					self.actuator2.reparentTo(render)
					self.actuator2.setPos(self.environment2.getPos())
					if p == 1:
						self.actuator2.setZ(self.actuator2.getZ())
						self.actuator2.setP(self.actuator2.getP()+180)
					self.actuator2.setScale(2)
					self.actuator2.setH(self.actuator2.getH()+180)
                                        self.array.append(self.actuator2)
					bounds = self.actuator2.getChild(0).getBounds()
					center = bounds.getCenter()
					radius = bounds.getRadius()-.5
					cSphere = CollisionSphere(center,radius)
					cNode = CollisionNode("actuator")
					cNode.addSolid(cSphere)
					cNodePath = self.actuator2.attachNewNode(cNode)
					#cNodePath.show()
				x1 = x1 + len

			for i in range(l):
				'''Left Half of stage'''
				self.environment = loader.loadModel("models/gamedev/platform")
				self.environment.reparentTo(render)
				self.environment.setScale(5)
				self.environment.setPos(x2,0,h)
                                self.array.append(self.environment)
				self.environment2 = loader.loadModel("models/gamedev/platform")
				self.environment2.reparentTo(render)
				self.environment2.setScale(5)
				self.environment2.setPos(x2+286,0,h)
                                self.array.append(self.environment2)

				if l == i+1:
					cSphere = CollisionSphere(Point3(-2,0,0),2)
					if i == 9:
						cNode = CollisionNode("lwall")
					else:
						cNode = CollisionNode("ledge")
					cNode.addSolid(cSphere)
					cNodePath = self.environment.attachNewNode(cNode)
					cNodePath = self.environment2.attachNewNode(cNode)
					#cNodePath.show()
				if a == -i:
					self.actCount+=1
					self.actuator = Actor("models/gamedev/actuator")
					self.actuator.reparentTo(render)
					self.actuator.setPos(self.environment.getPos())
					self.actuator.setScale(2)
                                        self.array.append(self.actuator)
					bounds = self.actuator.getChild(0).getBounds()
					center = bounds.getCenter()
					radius = bounds.getRadius()-.5
					cSphere = CollisionSphere(center,radius)
					cNode = CollisionNode("actuator")
					cNode.addSolid(cSphere)
					cNodePath = self.actuator.attachNewNode(cNode)
					#cNodePath.show()
					
					self.actuator = Actor("models/gamedev/actuator")
					self.actuator.reparentTo(render)
					self.actuator.setPos(self.environment2.getPos())
					self.actuator.setScale(2)
                                        self.array.append(self.actuator)
					bounds = self.actuator.getChild(0).getBounds()
					center = bounds.getCenter()
					radius = bounds.getRadius()-.5
					cSphere = CollisionSphere(center,radius)
					cNode = CollisionNode("actuator")
					cNode.addSolid(cSphere)
					cNodePath = self.actuator.attachNewNode(cNode)
					#cNodePath.show()
				x2 = x2 - len
			j+=1    
			h = h+40
			#x1 = 4.9
			#x2 = -4.9
			a = 0
		self.h = h+50
		x2b=x2o
		x1b=x1o
		
		print "end setupStage"

	def setupLighting(self):
		
		print "start setupLighting"
		
		ambientLight = AmbientLight('ambientLight')
		ambientLight.setColor(Vec4(0.55,0.55,0.55,1.0))
		ambientLightNP = render.attachNewNode(ambientLight)
		render.setLight(ambientLightNP)
		dirLight = DirectionalLight('dirLight')
		dirLight.setColor(Vec4(0.6,0.6,0.6,1))
		dirLightNP = render.attachNewNode(dirLight)
		dirLightNP.setHpr(Vec3(0.0,-26.0,0.0))
		render.setLight(dirLightNP)
		
		print "end setupLighting"
	
	def setupIntervals(self):
		
		print "start setupIntervals"
		
		self.charWalk1 = self.playerModel.actorInterval("walk")
		self.charWalk1.loop( )
		self.charWalk1.pause( )
		
		self.charWalk2 = self.playerModel2.actorInterval("walk2")
		self.charWalk2.loop( )
		self.charWalk2.pause( )
		
		self.jump1 = self.playerModel.actorInterval("jump")
		self.jump1.loop()
		self.jump1.pause()
		
		self.jump2 = self.playerModel2.actorInterval("jump2")
		self.jump2.loop()
		self.jump2.pause()
		
		self.climb1 = self.playerModel.actorInterval("climb")
		self.climb1.loop()
		self.climb1.pause()
		
		self.climb2 = self.playerModel2.actorInterval("climb2")
		self.climb2.loop()
		self.climb2.pause()
		
		print "end setupIntervals"
	
	# PLAYER ONE #

	def left(self):
		taskMgr.add(self.leftTask,'leftTask')
		self.charWalk1.loop()
		#end left
		
	def leftTask(self,task):
		if self.climbing1 == 0:
			self.playerModel.setH(270)
			self.playerModel.setPos(Vec3(self.playerModel.getX()-self.speed1, self.playerModel.getY(), self.playerModel.getZ()))
		return Task.cont

	def right(self):
		taskMgr.add(self.rightTask,'rightTask')
		self.charWalk1.loop()
		#end right
		
	def rightTask(self,task):
		if self.climbing1 == 0:
			self.playerModel.setH(90)
			self.playerModel.setPos(Vec3(self.playerModel.getX()+self.speed1, self.playerModel.getY(), self.playerModel.getZ()))
		return Task.cont	

	def climbable(self,cEntry):
		self.nodeCount1+=1
		print self.nodeCount1
		self.ignore("w")
		self.ignore("w-up")
		self.ignore("s")
		self.ignore("s-up")
		self.acceptOnce("w",self.climb,[1])
		self.accept("w-up",self.noClimb)
		self.acceptOnce("s",self.climb,[-1])
		self.accept("s-up",self.noClimb)

	def climb(self,dir):
		self.dir1 = dir
		self.climbing1 = 1
		self.climbSpeed1 = 1
		self.ignore("a")
		self.ignore("a-up")
		self.ignore("d")
		self.ignore("d-up")
		taskMgr.add(self.climbTask,'climbTask')
		self.climb1.loop()
		
	def noClimb(self):
		taskMgr.remove('climbTask')
		self.climb1.pause()
		if self.nodeCount1 == 0:
			self.climbing = 0
		self.climbSpeed1 = 0
		self.acceptOnce("w",self.climb,[1])
		self.acceptOnce("s",self.climb,[-1])
		
	def jumpable(self,cEntry):
		self.nodeCount1+=-1
		print self.nodeCount1
		if self.nodeCount1 == 0:
			taskMgr.remove('climbTask')
			self.ignore("w")
			self.ignore("w-up")
			self.ignore("s")
			self.ignore("s-up")
			self.acceptOnce("w",self.jump)
			self.acceptOnce("a",self.left)
			self.acceptOnce("d",self.right)
			self.accept("a-up",self.stopLeft)
			self.accept("d-up",self.stopRight)
			self.climbing1 = 0
			self.climbSpeed1 = 0
			self.climb1.pause()
			
	def walkable(self,cEntry):
		self.ignore("w")
		self.ignore("w-up")
		self.ignore("s")
		self.ignore("s-up")
		self.acceptOnce("w",self.climb,[1])
		self.accept("w-up",self.noClimb)
		self.acceptOnce("s",self.climb,[-1])
		self.accept("s-up",self.noClimb)
		self.acceptOnce("a",self.left)
		self.acceptOnce("d",self.right)
		self.accept("a-up",self.stopLeft)
		self.accept("d-up",self.stopRight)
		self.climbing1 = 0
		self.climbSpeed1 = 0
		self.climb1.pause()
			
	def climbTask(self,task):
		if self.playerModel.getZ() >=0:
			self.playerModel.setH(0)
			self.playerModel.setPos(Vec3(self.playerModel.getX(), self.playerModel.getY(), self.playerModel.getZ()+self.climbSpeed1*self.dir1))
		return Task.cont	
	
	def jump(self):
		if self.nodeCount1 == 0:
			self.ignore("w")
			self.ignore("w-up")
			z = self.playerModel.getZ()
			j = ProjectileInterval(self.playerModel, startPos = self.playerModel.getPos(), startVel = Point3(0,0,27), endZ = z)
			j.start()
			taskMgr.doMethodLater(3,self.jumpTask,"jumpTask")
		else:
			self.acceptOnce("w",self.climb,[1])
			
	def jumpTask(self, task):
		if self.climbing1 == 0:
			self.jump1.pause()
			self.acceptOnce("w",self.jump)
		#return task.cont

	def allowRight(self):
		self.acceptOnce("d",self.right)

	def noRight(self):
		taskMgr.remove('rightTask')
		self.charWalk1.pause()
		self.acceptOnce("d",self.right)

	def stopRight(self):
		self.noRight()
		#self.allowRight()
		
	def rightWall(self,cEntry):
		self.ignore("d")
		self.noRight()
		
	def rightEdge(self,cEntry):
		self.ignore("d")
		self.noRight()
				
	def rightOK(self,cEntry):
		self.allowRight()	
		
	def allowLeft(self):
		self.acceptOnce("a",self.left)

	def noLeft(self):
		taskMgr.remove('leftTask')
		self.charWalk1.pause()
		self.acceptOnce("a",self.left)

	def stopLeft(self):
		self.noLeft()
		#self.allowLeft()
		
	def leftWall(self,cEntry):
		self.ignore("a")
		self.noLeft()
		
	def leftEdge(self,cEntry):
		self.ignore("a")
		self.noLeft()
		
	def leftOK(self,cEntry):
		self.allowLeft()

	# PLAYERTWO #

	def left2(self):
		taskMgr.add(self.leftTask2,'leftTask2')
		self.charWalk2.loop()
		#end left
		
	def leftTask2(self,task):
		if self.climbing2 == 0:
			self.playerModel2.setH(0)
			self.playerModel2.setPos(Vec3(self.playerModel2.getX()-self.speed2, self.playerModel2.getY(), self.playerModel2.getZ()))
		return Task.cont

	def right2(self):
		taskMgr.add(self.rightTask2,'rightTask2')
		self.charWalk2.loop()
		#end right
		
	def rightTask2(self,task):
		if self.climbing2 == 0:
			self.playerModel2.setH(180)
			self.playerModel2.setPos(Vec3(self.playerModel2.getX()+self.speed2, self.playerModel2.getY(), self.playerModel2.getZ()))
		return Task.cont	

	def climbable2(self,cEntry):
		self.nodeCount2+=1
		#print self.nodeCount1
		self.ignore("o")
		self.ignore("o-up")
		self.ignore("l")
		self.ignore("l-up")
		self.acceptOnce("o",self.climbT2,[1])
		self.accept("o-up",self.noClimb2)
		self.acceptOnce("l",self.climbT2,[-1])
		self.accept("l-up",self.noClimb2)

	def climbT2(self,dir):
		self.dir2 = dir
		self.climbing2 = 1
		self.climbSpeed2 = 1
		self.ignore("k")
		self.ignore("k-up")
		self.ignore(";")
		self.ignore(";-up")
		taskMgr.add(self.climbTask2,'climbTask2')
		self.climb2.loop()
		
	def noClimb2(self):
		taskMgr.remove('climbTask2')
		self.climb2.pause()
		if self.nodeCount2 == 0:
			self.climbing2 = 0
		self.climbSpeed2 = 0
		self.acceptOnce("o",self.climbT2,[1])
		self.acceptOnce("l",self.climbT2,[-1])
		
	def jumpable2(self,cEntry):
		self.nodeCount2+=-1
		#print self.nodeCount2
		if self.nodeCount2 == 0:
			taskMgr.remove('climbTask2')
			self.ignore("o")
			self.ignore("o-up")
			self.ignore("l")
			self.ignore("l-up")
			self.acceptOnce("o",self.jumpT2)
			self.acceptOnce("k",self.left2)
			self.acceptOnce(";",self.right2)
			self.accept("k-up",self.stopLeft2)
			self.accept(";-up",self.stopRight2)
			self.climbing2 = 0
			self.climbSpeed2 = 0
			self.climb2.pause()
			
	def walkable2(self,cEntry):
		self.ignore("o")
		self.ignore("o-up")
		self.ignore("l")
		self.ignore("l-up")
		self.acceptOnce("o",self.climbT2,[1])
		self.accept("o-up",self.noClimb2)
		self.acceptOnce("l",self.climbT2,[-1])
		self.accept("l-up",self.noClimb2)
		self.acceptOnce("k",self.left2)
		self.acceptOnce(";",self.right2)
		self.accept("k-up",self.stopLeft)
		self.accept(";-up",self.stopRight)
		self.climbing2 = 0
		self.climbSpeed2 = 0
		self.climb2.pause()
			
	def climbTask2(self,task):
		if self.playerModel2.getZ() >=0:
			self.playerModel2.setH(90)
			self.playerModel2.setPos(Vec3(self.playerModel2.getX(), self.playerModel2.getY(), self.playerModel2.getZ()+self.climbSpeed2*self.dir2))
		return Task.cont	
	
	def jumpT2(self):
		if self.nodeCount2 == 0:
			self.ignore("o")
			self.ignore("o-up")
			z = self.playerModel2.getZ()
			j = ProjectileInterval(self.playerModel2, startPos = self.playerModel2.getPos(), startVel = Point3(0,0,27), endZ = z)
			j.start()
			taskMgr.doMethodLater(3,self.jumpTask2,"jumpTask2")
		else:
			self.acceptOnce("w",self.climb,[1])
			
	def jumpTask2(self, task):
		if self.climbing2 == 0:
			self.jump2.pause()
			self.acceptOnce("o",self.jumpT2)
		#return task.cont

	def allowRight2(self):
		self.acceptOnce(";",self.right2)

	def noRight2(self):
		taskMgr.remove('rightTask2')
		self.charWalk2.pause()
		self.acceptOnce(";",self.right2)

	def stopRight2(self):
		self.noRight2()
		#self.allowRight()
		
	def rightWall2(self,cEntry):
		self.ignore(";")
		self.noRight2()
		
	def rightEdge2(self,cEntry):
		self.ignore(";")
		self.noRight2()
				
	def rightOK2(self,cEntry):
		self.allowRight2()	
		
	def allowLeft2(self):
		self.acceptOnce("k",self.left2)

	def noLeft2(self):
		taskMgr.remove('leftTask2')
		self.charWalk2.pause()
		self.acceptOnce("k",self.left2)

	def stopLeft2(self):
		self.noLeft2()
		#self.allowLeft()
		
	def leftWall2(self,cEntry):
		self.ignore("k")
		self.noLeft2()
		
	def leftEdge2(self,cEntry):
		self.ignore("k")
		self.noLeft2()
		
	def leftOK2(self,cEntry):
		self.allowLeft2()

	def cameraFollowTask(self,task):
		base.camList[1].setPos(Vec3(self.playerModel.getX(),-200,self.playerModel.getZ()+30))
		base.camList[2].setPos(Vec3(self.playerModel2.getX(),-200,self.playerModel2.getZ()+30))
		return task.cont
	
	def activate(self,cEntry):
		i = cEntry.getIntoNodePath().getParent()
		where = i.getPos()
		which = i.getHpr()
		i.detachNode() 
		i = Actor("models/gamedev/actuatorOn")
		i.setName("actuatorOn")
		i.setPosHpr(where,which)
		i.setScale(2)
                i.reparentTo(render)
                self.array.append(i)
                
                if i.getX() < 144:
                        self.player1Score += 3
                else:
                        self.player2Score += 3

	def stun(self,cEntry):
		ow = Sequence(Func(self.startStun), Wait(3), Func(self.stopStun))
		ow.start()
	
	def startStun(self):
		self.speed1 = 0
		self.climbspeed1 = 0
		self.ignore("w")
		self.ignore("w-up")
		self.ignore("a")
		self.ignore("d")
		self.ignore("a-up")
		self.ignore("d-up")
		taskMgr.remove('leftTask')
		taskMgr.remove('rightTask')
		taskMgr.remove('climbTask')
		taskMgr.remove('jumpTask')
		self.playerModel.stop()
		#self.ignore("player1-ladder")
	
	def stopStun(self):
		self.speed1 = 3
		self.climbspeed1 = 1
		self.acceptOnce("a",self.left)
		self.acceptOnce("d",self.right)
		self.accept("a-up",self.stopLeft)
		self.accept("d-up",self.stopRight)
		self.acceptOnce("w",self.jump)
		#self.accept("player1-ladder", self.climbable)
	
	def stun2(self,cEntry):
		ow = Sequence(Func(self.startStun2), Wait(3), Func(self.stopStun2))
		ow.start()
	
	def startStun2(self):
		self.speed2 = 0
		self.climbspeed2 = 0
		self.ignore("k")
		self.ignore(";")
		self.ignore("k-up")
		self.ignore(";-up")
		self.ignore("o")
		self.ignore("o-up")
		taskMgr.remove('leftTask2')
		taskMgr.remove('rightTask2')
		taskMgr.remove('climbTask2')
		taskMgr.remove('jumpTask2')
		self.playerModel2.stop()
		#self.ignore("player2-ladder")
	
	def stopStun2(self):
		self.speed2 = 3
		self.climbspeed2 = 1
		self.acceptOnce("k",self.left2)
		self.acceptOnce(";",self.right2)
		self.accept("k-up",self.stopLeft2)
		self.accept(";-up",self.stopRight2)
		self.acceptOnce("o",self.jumpT2)
		#self.accept("player2-ladder", self.climbable2)

	def setupCollisions(self):
		
		print "start setupCollisions"
		
		self.cHandler = CollisionHandlerEvent()
		self.cHandler = CollisionHandlerEvent()
		self.cHandler.setInPattern("%fn-%in")
		self.cHandler.setAgainPattern("%fn-is-on-%in")        
		self.cHandler.setOutPattern("%fn-left-%in")
		self.cTrav = CollisionTraverser()
		base.cTrav = self.cTrav

		#Player 1 collision solid
		bounds = self.playerModel.getChild(0).getBounds()
		center = bounds.getCenter()-Vec3(0,0,12.5)
		radius = bounds.getRadius()-21
		cSphere = CollisionSphere(center,radius)
		cNode = CollisionNode("player1")
		cNode.addSolid(cSphere)
		
		centerB = bounds.getCenter()-Vec3(0,0,-11)
		radiusB = bounds.getRadius()-21
		cSphereB = CollisionSphere(centerB,radiusB)
		cNode.addSolid(cSphereB)
		cNodePath = self.playerModel.attachNewNode(cNode)
		#cNodePath.show()
		
		#centerBB = bounds.getCenter()-Vec3(0,0,25)
		#radiusBB = bounds.getRadius()-28
		#cSphereBB = CollisionSphere(centerB,radiusB)
		#cNodeT = CollisionNode("player1B")
		#cNodeT.addSolid(cSphereBB)
		#cNodePath = self.playerModel.attachNewNode(cNodeT)
		#cNodePath.show()

		#Player 2 collision solid
		bounds2 = self.playerModel2.getChild(0).getBounds()
		center2 = bounds2.getCenter()-Vec3(0,0,12.5)
		radius2 = bounds2.getRadius()-21
		cSphere2 = CollisionSphere(center2,radius2)
		cNode2 = CollisionNode("player2")
		cNode2.addSolid(cSphere2)
		
		bounds2B = self.playerModel2.getChild(0).getBounds()
		center2B = bounds2B.getCenter()-Vec3(0,0,-11)
		radius2B = bounds2B.getRadius()-21
		cSphere2B = CollisionSphere(center2B,radius2B)
		cNode2.addSolid(cSphere2B)
		cNodePath2 = self.playerModel2.attachNewNode(cNode2)
		#cNodePath2.show()

		self.cTrav.addCollider(cNodePath,self.cHandler)
		self.cTrav.addCollider(cNodePath2,self.cHandler)
		self.cTrav.addCollider(cNodePath,self.cHandler)
		self.cTrav.addCollider(cNodePath2,self.cHandler)

		self.accept("player1-ladder", self.climbable)
		self.accept("player1-left-ladder", self.jumpable)
		#self.accept("player1b-canWalk", self.walkable)
		self.accept("player2-ladder", self.climbable2)
		self.accept("player2-left-ladder", self.jumpable2)
		#self.accept("player1-platform", self.climbable)
		#self.accept("player1-left-platform",self.
		#self.accept("player1-left-ladder-down", self.noDrop)
		#self.accept("player2-ladder-down", self.drop2)
		#self.accept("player2-left-ladder-down", self.noDrop2)
		self.accept("player1-actuator", self.activate)
		self.accept("player2-actuator", self.activate)
		self.accept("player1-boulder", self.stun)
		self.accept("player2-boulder", self.stun2)
		self.accept("boulder-player1", self.stun)
		self.accept("boulder-player2", self.stun2)
		self.accept("player1-is-on-ledge", self.leftEdge)
		self.accept("player2-is-on-ledge", self.leftEdge2)
		self.accept("player1-is-on-redge", self.rightEdge)
		self.accept("player2-is-on-redge", self.rightEdge2)
		self.accept("player1-is-on-lwall", self.leftWall)
		self.accept("player2-is-on-lwall", self.leftWall2)
		self.accept("player1-is-on-rwall", self.rightWall)
		self.accept("player2-is-on-rwall", self.rightWall2)
		
		self.accept("player1-left-ledge", self.leftOK)
		self.accept("player2-left-ledge", self.leftOK2)
		self.accept("player1-left-redge", self.rightOK)
		self.accept("player2-left-redge", self.rightOK2)
		self.accept("player1-left-lwall", self.leftOK)
		self.accept("player2-left-lwall", self.leftOK2)
		self.accept("player1-left-rwall", self.rightOK)
		self.accept("player2-left-rwall", self.rightOK2)
		
		print "end setupCollisions"
	
	def boulderTask(self,task):
		drop1 = ProjectileInterval(self.boulder1, startPos = Point3(46+random.randint(-9,9)*9.8,0,self.h), startVel = Point3(0,0,0), endZ = -50)
	
		drop2 = ProjectileInterval(self.boulder2, startPos = Point3(253+random.randint(-9,9)*9.8,0,self.h),startVel = Point3(0,0,0), endZ = -50)
	
		dropBoth = Parallel(drop1,drop2)
		if self.boulder1.getZ() <= -50.0:
			drop1.start()
		if self.boulder2.getZ() <= -50.0:
			drop2.start()
	
		return task.cont
	
	def clockTask(self,task):
		self.timer.detachNode()
		self.timer = OnscreenText("%d" % (self.gameLen-globalClock.getRealTime(),), pos = (98,145), scale = 18.0)
		self.timer.setColor(1,1,1)
		self.timer.reparentTo(render)
		
		return Task.cont

	def endGame(self,task):
		taskMgr.removeTasksMatching('cameraFollowTask')
		taskMgr.removeTasksMatching('boulderTask')
		taskMgr.removeTasksMatching('clockTask')
			
		#base.camList[3].removeNode()
		#base.camList[2].removeNode()
		#base.camList[1].removeNode()
		
		base.makeCamera(base.win, displayRegion = (0, 1, 0, 1))
		
		self.music.stop()
	
                #self.destroy()

		self.music3  = loader.loadMusic("models/gamedev/CSTAR.mp3")
		self.music3.play()
	
	def getScores(self):
		return (self.player1Score, self.player2Score)
		
	def getGameLen(self):
		return self.gameLen
	
	def stopMusic(self):
		self.music3.stop()
	
	def destroy(self):	
		self.playerModel.detachNode()
		self.playerModel2.detachNode()
		self.divider.detachNode()
		self.background.destroy()
		self.timer.destroy()
                while len(self.array) > 0:
                        print len(self.array)
                        self.array[0].remove()
                        del self.array[0]
		
#world = World()
#run()