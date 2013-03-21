import direct.directbase.DirectStart
from pandac.PandaModules import *
from direct.showbase.DirectObject import DirectObject
from direct.actor.Actor import Actor
from direct.interval.IntervalGlobal import *
from direct.task import Task
import sys
import math #trig function and pi!
import random
import balls
from direct.gui.OnscreenImage import OnscreenImage
from direct.gui.OnscreenText import OnscreenText 
from direct.gui.DirectGui import *

class Lvl02(DirectObject):

	#constructor
	def start(self):	

		base.disableMouse() #turn off mouse camera control

		camera.setPosHpr(Vec3(0,-55,30), Vec3(0,-20,0))
		self.ballNum = 34
		self.loadModels()
		self.setupLighting()
		self.setupCollisions()
		self.setupIntervals()
			
		#self.clock = ClockObject
		
		self.gameLen = 60
		
		self.music = loader.loadMusic("models/gamedev/DFC.mp3")
		self.music.play()
		
		self.hud = DirectFrame(image = 'models/gamedev/lvl2hud.jpg')
		self.hud['pos'] = (-100,0,-100)
		self.hud['frameSize'] = (0,0,0,0)
		self.hud['image_pos'] = (0,-10,24.5)
		self.hud['image_scale'] = (22.25,1,2)
		self.hud['image_hpr'] = (0,-45,0)
		self.hud.reparentTo(render)
	
		globalClock.reset()
		self.drop()
		self.timer = DirectFrame(text = "%d" % (self.gameLen-globalClock.getRealTime(),), pos = Vec3(0,-11.5,23.5),text_fg = (1,1,1,1),text_scale=4.0)
		self.timer['frameSize'] = (0,0,0,0)
		self.timer.reparentTo(render)
		taskMgr.add(self.clockTask,"clockTask")
		
		self.player1Score = 0
		self.player2Score = 0
		
		self.speed1 = 8.0
		self.speed2 = 8.0
		self.turnSpeed1 = 80.0
		self.turnSpeed2 = 80.0
		
		self.ignoreColl= 0
		
		self.player1IsColliding = 0
		self.player2IsColliding = 0
		
		taskMgr.doMethodLater(self.gameLen, self.endGame,'gameFinished')
		
		taskMgr.doMethodLater(self.gameLen/2.0,self.changeMusic,'musicSwitch')
		
		#setup key controls
		self.accept("escape",sys.exit)

		# Player 1 movement

		self.acceptOnce("w",self.walk)
		self.acceptOnce("a",self.turn,[-1])
		self.acceptOnce("d",self.turn,[1])
		
		self.accept("w-up",self.stopWalk)
		self.accept("a-up",self.stopTurn)
		self.accept("d-up",self.stopTurn)
		
		# Player 2 movement

		self.acceptOnce("o",self.walk2,)
		self.acceptOnce("k",self.turn2,[-1])
		self.acceptOnce(";",self.turn2,[1])

		self.accept("o-up",self.stopWalk2)
		self.accept("k-up",self.stopTurn2)
		self.accept(";-up",self.stopTurn2)

	def loadModels(self):
		
		self.environment = loader.loadModel("models/gamedev/grassy")
		self.environment.reparentTo(render)
		self.environment.setScale(3.4)
		self.environment.setPos(0,12,-0.45)
		self.environment.setH(78)

		self.background = OnscreenImage(image = 'models/gamedev/lvl2background.jpg', pos = (0,40,0),scale=42.5, hpr = (0,-1,0))
		self.background.reparentTo(render)

		bounds = self.environment.getChild(0).getBounds()
		radius = bounds.getRadius()*1.5
		center = bounds.getCenter()+Vec3(0,12,0)
	
		#print center
	
		self.ball = []
		for i in range(self.ballNum+1):
			balls.define(self.ball,i,render,center,radius)

		# ** Load male character that will represent first player** #
		
		self.playerModel = Actor("models/gamedev/redguy-model",{"walk":"models/gamedev/redguy-run"})
		self.playerModel.reparentTo(render)
		self.playerModel.setScale(.1)
		self.playerModel.setH(90)

		# ** Position player at center of the field with it lying directly above the field. ** #
		self.playerModel.setPos(-10,0,0.76)

		# ** Load female character that will represent second player** #
		
		self.playerModel2 = Actor("models/gamedev/bluegirl-model",{"walk2":"models/gamedev/bluegirl-run"})
		self.playerModel2.reparentTo(render)
		self.playerModel2.setScale(.1)
		self.playerModel2.setH(0)

		# ** Position player at center of the field with it lying directly above the field. ** #

		self.playerModel2.setPos(10,0,1.0)

	def setupLighting(self):
		ambientLight = AmbientLight('ambientLight')
		ambientLight.setColor(Vec4(0.55,0.55,0.55,1.0))
		ambientLightNP = render.attachNewNode(ambientLight)
		render.setLight(ambientLightNP)
		dirLight = DirectionalLight('dirLight')
		dirLight.setColor(Vec4(0.6,0.6,0.6,1))
		dirLightNP = render.attachNewNode(dirLight)
		dirLightNP.setHpr(Vec3(0.0,-26.0,0.0))
		render.setLight(dirLightNP)

	def setupIntervals(self):
		self.charWalk1 = self.playerModel.actorInterval("walk")
		self.charWalk1.loop()
		self.charWalk1.pause()

		self.charWalk2 = self.playerModel2.actorInterval("walk2")
		self.charWalk2.loop( )
		self.charWalk2.pause( )

	def drop(self):
		dist = 49

		for i in range(self.ballNum+1):
			ballDrop = self.ball[i].posInterval(5.0,Vec3(self.ball[i].getX(),self.ball[i].getY(),self.ball[i].getZ()-dist))
			ballDrop.start()

	def dropSingle(self):
		dist = 49

		ballDrop = self.ball[self.ballNum].posInterval(5.0,Vec3(self.ball[self.ballNum].getX(),self.ball[self.ballNum].getY(),self.ball[self.ballNum].getZ()-dist))
		ballDrop.start()
				
	# #################
	# Begin definitions for tasks:  #
	# #################
	

	def walk(self):
		taskMgr.add(self.walkTask,'walkTask')
		self.charWalk1.loop()
	# end walk

	def stopWalk(self):
		taskMgr.remove('walkTask')
		self.charWalk1.pause()
		self.acceptOnce("w",self.walk)	
	# end stopWalk

	def walkTask(self,task):
		dt = globalClock.getDt()
		dist = self.speed1*dt
		angle = (self.playerModel.getH())*math.pi/180.0
		dx = dist*math.sin(angle)
		dy = dist*-math.cos(angle)
		self.playerModel.setPos(Vec3(self.playerModel.getX()+dx,self.playerModel.getY()+dy,self.playerModel.getZ()))
		return Task.cont
	# end walkTask

	def turn(self,dir):
		taskMgr.add(self.turnTask,'turnTask',extraArgs=[dir])
		#self.charTurn1.loop()
		self.ignore("a")
		self.ignore("d")
	# end turn

	def stopTurn(self):
		taskMgr.remove('turnTask')
		self.acceptOnce("a",self.turn,[-1])
		self.acceptOnce("d",self.turn,[1])
	# end stopTurn

	def turnTask(self,dir):
		dt = globalClock.getDt()
		angle = dir*self.turnSpeed1*dt
		self.playerModel.setH(self.playerModel.getH()-angle)
		return Task.cont
	# end turnTask

    # Player 2's Movement #

	def walk2(self):
		taskMgr.add(self.walkTask2,'walkTask2')
		self.charWalk2.loop()
	# end walk

	def stopWalk2(self):
		taskMgr.remove('walkTask2')
		self.charWalk2.pause()
		self.acceptOnce("o",self.walk2)
		# end stopWalk

	def walkTask2(self,task):
		dt = globalClock.getDt()
		dist = self.speed2*dt
		angle = (self.playerModel2.getH()-90)*math.pi/180.0
		dx = dist*math.sin(angle)
		dy = dist*-math.cos(angle)

		self.playerModel2.setPos(Vec3(self.playerModel2.getX()+dx,self.playerModel2.getY()+dy,self.playerModel2.getZ()))
		return Task.cont
		# end walkTask

	def turn2(self,dir):
		taskMgr.add(self.turnTask2,'turnTask2',extraArgs=[dir])
		self.ignore("k")
		self.ignore(";")
		# end turn

	def stopTurn2(self):
		taskMgr.remove('turnTask2')
		self.acceptOnce("k",self.turn2,[-1])
		self.acceptOnce(";",self.turn2,[1])
		# end stopTurn

	def turnTask2(self,dir):
		dt = globalClock.getDt()
		angle = dir*self.turnSpeed2*dt
		self.playerModel2.setH(self.playerModel2.getH()-angle)
		return Task.cont
		# end turnTask	

	def setupCollisions(self):
		self.cHandler = CollisionHandlerEvent()
		self.cHandler.setInPattern("ate-%in")
		self.cHandler.addInPattern('%fn-into-%in')        
		self.cHandler.setAgainPattern('%fn-again-%in')          
		self.cHandler.setOutPattern('%fn-outof-%in')        
		self.cTrav = CollisionTraverser()
		base.cTrav = self.cTrav

		#Player 1 collision solid
		
		bounds = self.playerModel.getChild(0).getBounds()
		center = bounds.getCenter()-Vec3(0,0,12)
		radius = bounds.getRadius()-18
		boundsB = self.playerModel.getChild(0).getBounds()
		centerB = bounds.getCenter()-Vec3(0,0,-4)
		radiusB = bounds.getRadius()-20
		cSphere = CollisionSphere(center,radius)
		cSphereB = CollisionSphere(centerB,radiusB)
		cNode = CollisionNode("player1")
		cNode.addSolid(cSphere)
		cNode.addSolid(cSphereB)
		cNodePath = self.playerModel.attachNewNode(cNode)
		#cNodePath.show()
	
		#Player 2 collision solid
		bounds2 = self.playerModel2.getChild(0).getBounds()
		center2 = bounds2.getCenter()-Vec3(0,0,-4)
		radius2 = bounds2.getRadius()-20
		cSphere2 = CollisionSphere(center2,radius2)
		bounds2B = self.playerModel2.getChild(0).getBounds()
		center2B = bounds2B.getCenter()-Vec3(0,0,12)
		radius2B = bounds2B.getRadius()-18
		cSphere2B = CollisionSphere(center2B,radius2B)
		cNode2 = CollisionNode("player2")
		cNode2.addSolid(cSphere2)
		cNode2.addSolid(cSphere2B)
		cNodePath2 = self.playerModel2.attachNewNode(cNode2)
		#cNodePath2.show()

		self.cTrav.addCollider(cNodePath,self.cHandler)
		self.cTrav.addCollider(cNodePath2,self.cHandler)
		self.cTrav.addCollider(cNodePath,self.cHandler)
		self.cTrav.addCollider(cNodePath2,self.cHandler)       

		bounds = self.environment.getChild(0).getBounds()
		center = bounds.getCenter()
		radius = bounds.getRadius()*.71
		#print radius
		cSphere = CollisionInvSphere(center,radius)
		cNode = CollisionNode("Arena")
		cNode.addSolid(cSphere)
		cNodePath = self.environment.attachNewNode(cNode)
		#cNodePath.show()


		for i in range(self.ballNum+1):
			boundsB = self.ball[i].getChild(0).getBounds()
			centerB = boundsB.getCenter()
			radiusB = boundsB.getRadius()*.8
			cSphereB = CollisionSphere(centerB,radiusB)
			cNodeB = CollisionNode("ball")
			cNodeB.addSolid(cSphereB)
			cNodePathB = self.ball[i].attachNewNode(cNodeB)
			#cNodePath3.show()
		
		self.accept("ate-ball", self.eat)
		self.accept( 'player1-into-Arena', self.colliding1)
		self.accept( 'player1-again-Arena', self.colliding1)
		self.accept( 'player1-outof-Arena', self.notColliding1)
	
		self.accept( 'player2-into-Arena', self.colliding2)
		self.accept( 'player2-again-Arena', self.colliding2)
		self.accept( 'player2-outof-Arena', self.notColliding2)
		
		self.accept( 'player1-into-player2', self.colliding1)
		self.accept( 'player1-again-player2', self.colliding1)
		self.accept( 'player1-outof-player2', self.notColliding1)
		
		self.accept( 'player2-into-player1', self.colliding2)
		self.accept( 'player2-again-player1', self.colliding2)
		self.accept( 'player2-outof-player1', self.notColliding2)

	def eat(self,cEntry):
		if str(cEntry.getIntoNodePath().getParent()) == "render/blueball": #Blue ball picked up, update score
			self.player2Score+=1

		elif str(cEntry.getIntoNodePath().getParent()) == "render/redball": #Red ball picked up, update score
			self.player1Score+=1

		elif str(cEntry.getIntoNodePath().getParent()) == "render/crystalball":  #Freezes the field (Ice)
			self.environment.setColor(0,.9,1)
			taskMgr.doMethodLater(10, self.switch, 'changeStage') 
			self.speed1 = 14
			self.speed2 = 14
			self.turnSpeed1 = 110
			self.turnSpeed2 = 110
			taskMgr.doMethodLater(10, self.returnSpeeds, 'returnSpeedsToNormal') 

		elif str(cEntry.getIntoNodePath().getParent()) == "render/red_blue": #Switch Sphere Colors
			for i in self.ball:
				if i.getName() == "blueball":
					i.removeNode() 
					children = i.getGeomNode().getChildren() 
					children.detach() 
					i.loadModel("models/gamedev/redball") 
					i.setName("redball")
					i.reparentTo(render) 
	
				elif i.getName() == "redball":
					i.removeNode() 
					children = i.getGeomNode().getChildren() 
					children.detach() 
					i.loadModel("models/gamedev/blueball")
					i.setName("blueball")					
					i.reparentTo(render) 
	
		elif str(cEntry.getIntoNodePath().getParent()) == "render/fireball": #Stop your opponent for a few seconds
			if (str(cEntry.getFromNodePath().getParent()) == "render/redgirl") or (str(cEntry.getFromNodePath().getParent()) == "render/redguy"):
				self.speed2 = 0
				self.turnSpeed2 = 0
				self.ignore("o")
				taskMgr.doMethodLater(3, self.returnSpeeds2, 'returnSpeedsToNormal') 
			else:
				self.speed1 = 0
				self.turnSpeed1 = 0
				self.ignore("w")
				taskMgr.doMethodLater(3, self.returnSpeeds2, 'returnSpeedsToNormal') 
	
		elif str(cEntry.getIntoNodePath().getParent()) == "render/black_white":
			self.ignoreColl = 1
			x = Vec3(self.playerModel.getPos())
			y = Vec3(self.playerModel2.getPos())
			self.playerModel.setPos(y)
			self.playerModel2.setPos(x)
			self.ignoreColl = 0

		elif str(cEntry.getIntoNodePath().getParent()) == "render/golden":
			if (str(cEntry.getFromNodePath().getParent()) == "render/redgirl") or (str(cEntry.getFromNodePath().getParent()) == "render/redguy"):
				self.speed1 = 14
				self.turnSpeed1 = 110
				taskMgr.doMethodLater(8, self.returnSpeeds3, 'returnSpeedsToNormal') 
			else:
				self.speed2 = 14
				self.turnSpeed2 = 110
				taskMgr.doMethodLater(8, self.returnSpeeds3, 'returnSpeedsToNormal') 
	
		elif str(cEntry.getIntoNodePath().getParent()) == "render/greenball":
			if (str(cEntry.getFromNodePath().getParent()) == "render/redgirl") or (str(cEntry.getFromNodePath().getParent()) == "render/redguy"):
				self.player1Score += 5
			else:
				self.player2Score += 5

		elif str(cEntry.getIntoNodePath().getParent()) == "render/blackball":
			camera.setPosHpr(Vec3(0,-55,110), Vec3(0,-20,0))
			taskMgr.doMethodLater(5,self.restoreCamera,'restoreCamera')
	
		elif str(cEntry.getIntoNodePath().getParent()) == "render/translucent":
			for i in self.ball:
				i.hide()
				taskMgr.doMethodLater(6,self.showBalls,'returnBallsToNormal')
	
		cEntry.getIntoNodePath().getParent().removeNode()
		
		#Drop a New Ball
		
		bounds = self.environment.getChild(0).getBounds()
		radius = bounds.getRadius()*1.8
		center = bounds.getCenter()+Point3(0,10,0)
		self.ballNum+=1
		balls.define(self.ball,self.ballNum,render,center,radius)
		
		boundsB = self.ball[self.ballNum].getChild(0).getBounds()
		centerB = boundsB.getCenter()
		radiusB = boundsB.getRadius()*.8
		cSphereB = CollisionSphere(centerB,radiusB)
		cNodeB = CollisionNode("ball")
		cNodeB.addSolid(cSphereB)
		cNodePathB = self.ball[self.ballNum].attachNewNode(cNodeB)
		
		self.dropSingle()

	def showBalls(self,task):
		for i in self.ball:
			i.show()

	def restoreCamera(self,task):
		camera.setPosHpr(Vec3(0,-55,30), Vec3(0,-20,0))

	def switch(self,task):
		self.environment.removeNode()
		self.environment = loader.loadModel("models/gamedev/grassy")
		self.environment.reparentTo(render)
		self.environment.setScale(3.4)
		self.environment.setPos(0,12,-0.45)
		self.environment.setH(78)

	def colliding1( self, collEntry ): # accept a collision entry argument    
		if self.ignoreColl == 0:
			self.player1IsColliding = 1 # we are colliding        
			self.stopWalk( ) # pause all walking animation and movement        
			disp = ( collEntry.getSurfacePoint( render ) - collEntry.getInteriorPoint( render ) )
			newPos = self.playerModel.getPos( ) + disp # get new position
			self.playerModel.setPos( newPos ) # and set it to tiny's position
	# end colliding        

	def notColliding1( self, collEntry ): 
		self.player1IsColliding = 0    

	def colliding2( self, collEntry ): # accept a collision entry argument 
		if self.ignoreColl == 0:
			self.player2IsColliding = 1 # we are colliding        
			self.stopWalk2( ) # pause all walking animation and movement               
			disp = ( collEntry.getSurfacePoint( render ) - collEntry.getInteriorPoint( render ) )
			newPos = self.playerModel2.getPos( ) + disp # get new position
			self.playerModel2.setPos( newPos ) # and set it to tiny's position
	# end colliding        

	def notColliding2( self, collEntry ): 
		self.player2IsColliding = 0    

	def returnSpeeds(self,task):
		self.speed1 = 8.0
		self.speed2 = 8.0
		self.turnSpeed1 = 80.0
		self.turnSpeed2 = 80.0

	def returnSpeeds2(self,task):
		self.acceptOnce("w",self.walk)
		self.acceptOnce("o",self.walk2)
		self.speed1 = 8.0
		self.speed2 = 8.0
		self.turnSpeed1 = 80.0
		self.turnSpeed2 = 80.0

	def returnSpeeds3(self,task):
		self.speed1 = 8.0
		self.speed2 = 8.0
		self.turnSpeed1 = 80.0
		self.turnSpeed2 = 80.0

	def changeMusic(self,task):
		self.music.stop()
		self.music2  = loader.loadMusic("models/gamedev/ADRENALINE.mp3")
		self.music2.play()

	def clockTask(self,task):
		self.timer.removeNode()
		self.timer = DirectFrame(text = "%d" % (self.gameLen-globalClock.getRealTime(),), pos = Vec3(0,-11.5,23.5),text_fg = (1,1,1,1),text_scale= 4.0)
		self.timer['frameSize'] = (0,0,0,0)
		self.timer.reparentTo(render)
		return Task.cont

	def endGame(self,task):
		taskMgr.removeTasksMatching('returnSpeedsToNormal')
		taskMgr.removeTasksMatching('restoreCamera')
		taskMgr.removeTasksMatching('clockTask')
		taskMgr.removeTasksMatching('walkTask')
		taskMgr.removeTasksMatching('walkTask2')
		taskMgr.removeTasksMatching('turnTask')
		taskMgr.removeTasksMatching('turnTask2')

		self.music2.stop()
		self.music3  = loader.loadMusic("models/gamedev/CSTAR.mp3")
		self.music3.play()

		self.speed1 = 0
		self.speed2 = 0
		self.turnSpeed1 = 0.0
		self.turnSpeed2 = 0.0
		
	def getScores(self):
		return (self.player1Score, self.player2Score)
		
	def getGameLen(self):
		return self.gameLen
		
	def stopMusic(self):
		self.music3.stop()
		
	def destroy(self):
		self.hud.destroy()
		self.timer.destroy()
		self.environment.removeNode()
		self.playerModel.removeNode()
		self.playerModel2.removeNode()
		self.background.destroy()
		
		for i in range(self.ballNum+1):
			self.ball[i].removeNode()

#lvl02 = Lvl02()
#run()