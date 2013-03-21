import direct.directbase.DirectStart
from pandac.PandaModules import *
from direct.showbase.DirectObject import DirectObject
from direct.actor.Actor import Actor
from direct.interval.IntervalGlobal import *
from direct.task import Task
import sys
import math #trig function and pi!
import random
import weapBalls
from direct.gui.OnscreenImage import OnscreenImage
from direct.gui.OnscreenText import OnscreenText
from direct.particles.ParticleEffect import ParticleEffect
from direct.particles.Particles import Particles
from direct.particles.ForceGroup import ForceGroup

class Lvl03(DirectObject):
    def start(self):
        base.disableMouse() #turn off mouse camera control
        base.enableParticles()
	
	self.music = loader.loadMusic("models/gamedev/DEC.mp3")
	self.music.play()
	
        camera.setPosHpr(Vec3(98,-390,90), Vec3(0,-5,0))
        self.ballNum = 10
	self.setupStage()
        self.loadModels()
        self.setupLighting()
        self.setupCollisions()
        self.setupIntervals()
	
	taskMgr.add(self.ballMovementTask,'ballMoveTask')
        
        self.gameLen = 30
        
	self.player1Weapon = ""
	self.player2Weapon = ""
	
        #hud = OnscreenImage(image = 'models/gamedev/lvl2hud.jpg', pos = (0,1,20),scale=5.0)
        #hud.reparentTo(render)
        
        globalClock.reset()
        
        self.timer = OnscreenText("%d" % (self.gameLen-globalClock.getRealTime(),), pos = (98,145), scale = 18.0)
        self.timer.setColor(1,1,1)
        taskMgr.add(self.clockTask,"clockTask")
        
        self.player1Score = 0
        self.player2Score = 0
        
        self.nodeCount1 = 0
        self.nodeCount2 = 0
	
	self.player1Invincible = 0
        self.player2Invincible = 0
	
	self.jNP = self.playerModel.exposeJoint(None,"modelRoot","ikHandle2")
	self.jNP2 = self.playerModel2.exposeJoint(None,"modelRoot","ikHandle2")
	
        self.climbing1 = 0
        self.climbing2 = 0
        
        self.speed1 = 3.0
        self.speed2 = 3.0
        
        self.ignoreColl= 0
        
        self.player1IsColliding = 0
        self.player2IsColliding = 0
        
        taskMgr.doMethodLater(self.gameLen, self.endGame,'gameFinished')
        
        #taskMgr.doMethodLater(self.gameLen/2.0,self.changeMusic,'musicSwitch')
        
        
        #setup key controls
        self.accept("escape",sys.exit)
        #self.acceptOnce("space",self.drop)
        # Player 1 movement
        
        self.acceptOnce("a",self.left)
        self.acceptOnce("d",self.right)
        
        self.accept("a-up",self.stopLeft)
        self.accept("d-up",self.stopRight)
        
        self.acceptOnce("w", self.jump)

        
        #Player 2 movement keys
        #self.accept("l",self.fall2)
        
        self.acceptOnce("k",self.left2)
        self.acceptOnce(";",self.right2)
        
        self.accept("k-up",self.stopLeft2)
        self.accept(";-up",self.stopRight2)
        
        self.acceptOnce("o", self.jumpT2)
        
    def setupStage(self):
	self.ball = []
	self.movement = []
	for i in range(self.ballNum+1):
		z=random.randint(1,2)
		if z ==1:
			z=-1
		else:
			z=1
		weapBalls.define(self.ball,i,render)
		self.movement.append(Vec3(random.random()*z,0,random.random()*z))
		#self.movement[i].Vec3(random.randint(1,3),0,random.randint(1,3))
		
	self.background2 = OnscreenImage(image = 'models/gamedev/frozenbg.JPG', pos = (98,10,0),scale=500)
	self.background2.detachNode()
        self.background = OnscreenImage(image = 'models/gamedev/moltenbg.JPG', pos = (98,10,0),scale=500)
        self.background.reparentTo(render)
        
        self.lava = loader.loadModel("models/gamedev/lava")
        self.lava.setPosHpr(Vec3(98,0,-18),Vec3(0,5,0))
        self.lava.setScale(50)
        self.lava.reparentTo(render)
        
        
        x1= 196
        x2 = 0
        m1 = 98
        m2 = 107.8
        len = 9.8
        h = 0
        a = 0
        p = 0
        
        for j in range(4):
            if j > 0:
                x1Old = x1
                x2Old = x2
                x1 = 196-(random.randint(0,3)*9.8)
                x2 = 0+random.randint(0,3)*9.8
                m1=98-(random.randint(0,3)*9.8)
                m2= 107.8+random.randint(0,3)*9.8
            
                for count in range(1):
                    l = random.randint(2,5)
                    r = random.randint(2,5)
                    c1 = random.randint(2,5)
                    c2 = random.randint(2,5)
                    if l+r < 4:
		        count = 0
			
            else:
                l = 4
                r = 4
                c1 = 2
                c2 = 2
            '''
            if j ==1 or j == 3:
                self.ladder = loader.loadModel("models/gamedev/ladder")
                self.ladder.reparentTo(render)
                self.ladder.setScale(1.5)
                self.ladder.setPos(x2+4.9,0,h-20)
                self.ladder2 = loader.loadModel("models/gamedev/ladder")
                self.ladder2.reparentTo(render)
                self.ladder2.setScale(1.5)
                self.ladder2.setPos(x1-4.9,0,h-20)
            
            if j == 2:
                self.ladder = loader.loadModel("models/gamedev/ladder")
                self.ladder.reparentTo(render)
                self.ladder.setScale(1.5)
                self.ladder.setPos(m1-4.9,0,h-20)
                self.ladder2 = loader.loadModel("models/gamedev/ladder")
                self.ladder2.reparentTo(render)
                self.ladder2.setScale(1.5)
                self.ladder2.setPos(m2+4.9,0,h-20)
            '''
            self.first = 1

            for i in range(r):
                '''Right half of stage'''
                self.environment = loader.loadModel("models/gamedev/platform")
                self.environment.reparentTo(render)
                self.environment.setScale(5)
                self.environment.setPos(x1,0,h)
                    
                if self.first == 1:
                    self.first = 0
                    bounds = self.environment.getChild(0).getBounds()
                    center = bounds.getCenter()
                    poly1 = Point3(center.getX()+1, center.getY()-.5, center.getZ()+.2)
                    poly2 = Point3(center.getX()-(2*r-1), center.getY()-.5, center.getZ()+.2)
                    poly3 = Point3(center.getX()+1, center.getY()+.5, center.getZ()+.2)
                    poly4 = Point3(center.getX()-(2*r-1), center.getY()+.5, center.getZ()+.2)
                    cPoly = CollisionPolygon(poly4, poly2, poly1, poly3)
                    cNode = CollisionNode("platform")
                    cNode.addSolid(cPoly)
                    cNodePath = self.environment.attachNewNode(cNode)
                    cNodePath.show()
                    
                x1 = x1 - len

            self.first = 1
            
            for i in range(l):
                '''Left Half of stage'''
                self.environment = loader.loadModel("models/gamedev/platform")
                self.environment.reparentTo(render)
                self.environment.setScale(5)
                self.environment.setPos(x2,0,h)
                
                if self.first == 1:
                    self.first = 0
                    bounds = self.environment.getChild(0).getBounds()
                    center = bounds.getCenter()
                    poly1 = Point3(center.getX()+(2*l-1), center.getY()-.5, center.getZ()+.2)
                    poly2 = Point3(center.getX()-1, center.getY()-.5, center.getZ()+.2)
                    poly3 = Point3(center.getX()+(2*l-1), center.getY()+.5, center.getZ()+.2)
                    poly4 = Point3(center.getX()-1, center.getY()+.5, center.getZ()+.2)
                    cPoly = CollisionPolygon(poly4, poly2, poly1, poly3)
                    cNode = CollisionNode("platform")
                    cNode.addSolid(cPoly)
                    cNodePath = self.environment.attachNewNode(cNode)
                    cNodePath.show()
                
                x2 = x2 + len
                
            self.first = 1
            
            for i in range(c1):
                '''Right half of stage'''
                self.environment = loader.loadModel("models/gamedev/platform")
                self.environment.reparentTo(render)
                self.environment.setScale(5)
                self.environment.setPos(m1,0,h)
                
                if self.first == 1:
                    self.first = 0
                    bounds = self.environment.getChild(0).getBounds()
                    center = bounds.getCenter()
                    poly1 = Point3(center.getX()+1, center.getY()-.5, center.getZ()+.2)
                    poly2 = Point3(center.getX()-(2*c1-1), center.getY()-.5, center.getZ()+.2)
                    poly3 = Point3(center.getX()+1, center.getY()+.5, center.getZ()+.2)
                    poly4 = Point3(center.getX()-(2*c1-1), center.getY()+.5, center.getZ()+.2)
                    cPoly = CollisionPolygon(poly4, poly2, poly1, poly3)
                    cNode = CollisionNode("platform")
                    cNode.addSolid(cPoly)
                    cNodePath = self.environment.attachNewNode(cNode)
                    cNodePath.show()
                
                m1 = m1 - len
                
            self.first = 1
            
            for i in range(c2):
                '''Left Half of stage'''
                self.environment = loader.loadModel("models/gamedev/platform")
                self.environment.reparentTo(render)
                self.environment.setScale(5)
                self.environment.setPos(m2,0,h)
                
                if self.first == 1:
                    self.first = 0
                    bounds = self.environment.getChild(0).getBounds()
                    center = bounds.getCenter()
                    poly1 = Point3(center.getX()+(2*c2-1), center.getY()-.5, center.getZ()+.2)
                    poly2 = Point3(center.getX()-1, center.getY()-.5, center.getZ()+.2)
                    poly3 = Point3(center.getX()+(2*c2-1), center.getY()+.5, center.getZ()+.2)
                    poly4 = Point3(center.getX()-1, center.getY()+.5, center.getZ()+.2)
                    cPoly = CollisionPolygon(poly4, poly2, poly1, poly3)
                    cNode = CollisionNode("platform")
                    cNode.addSolid(cPoly)
                    cNodePath = self.environment.attachNewNode(cNode)
                    cNodePath.show()
                
                m2 = m2 + len
            
            h = h+40
            a = 0

    def loadModels(self):
    
        # ** Load female character that will represent first player** #
        
        
        self.playerModel = Actor("models/gamedev/redguy-model",{"walk":"models/gamedev/redguy-run"})
        self.playerModel.reparentTo(render)
        self.playerModel.setScale(.6)
        self.playerModel.setH(90)
        
        # ** Position player at center of the field with it lying directly above the field. ** #
        
        self.playerModel.setPos(0,0,1.76)
        
        # ** Load female character that will represent second player** #
        
        self.playerModel2 = Actor("models/gamedev/bluegirl-model",{"walk2":"models/gamedev/bluegirl-run"})
        self.playerModel2.reparentTo(render)
        self.playerModel2.setScale(.6)
        self.playerModel2.setH(0)
        
        # ** Position player at center of the field with it lying directly above the field. ** #
        
        self.playerModel2.setPos(196,0,2.0)

    def reset(self):
	self.an1.getPhysicsObject().setVelocity(Vec3(0,0,0))
	self.an2.getPhysicsObject().setVelocity(Vec3(0,0,0))
	self.an1.getPhysicsObject().setPosition(Point3(0,0,11.76))
	self.an2.getPhysicsObject().setPosition(Point3(196,0,22.0))
	
	self.playerModel.setH(90)
	self.playerModel.detachNode()
	self.playerModel.setPos(0,0,1.76)
	self.anp.setFluidPos(Point3(0,0,1.76))
	self.playerModel.reparentTo(self.anp)
	
	self.playerModel2.setH(0)
	self.playerModel2.detachNode()
	self.playerModel2.setPos(196,0,22.0)
	self.anp2.setFluidPos(Point3(196,0,22.0))
	self.playerModel2.reparentTo(self.anp2)

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
        self.charWalk1l = self.playerModel.actorInterval("walk")
        self.charWalk1l.loop( )
        self.charWalk1l.pause( )
        
        self.charWalk1r = self.playerModel.actorInterval("walk")
        self.charWalk1r.loop( )
        self.charWalk1r.pause( )
        
        self.charWalk2l = self.playerModel2.actorInterval("walk2")
        self.charWalk2l.loop( )
        self.charWalk2l.pause( )
        
        self.charWalk2r = self.playerModel2.actorInterval("walk2")
        self.charWalk2r.loop( )
        self.charWalk2r.pause( )
        
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
        
        # end setupIntervals

        # ############################
        # Actual Working movement code
        # ############################

    def rise(self):
        dist = 40
        self.playerModel.setH(0)
        playerJump = self.playerModel.posInterval(1.0,Vec3(self.playerModel.getX(), self.playerModel.getY(),self.playerModel.getZ()+dist))
        playerJump.start()
        
    def rise2(self):
        dist = 40
        self.playerModel2.setH(90)
        playerJump2 = self.playerModel2.posInterval(1.0,Vec3(self.playerModel2.getX(), self.playerModel2.getY(),self.playerModel2.getZ()+dist))
        playerJump2.start()
        
    # PLAYER ONE #
        
    def left(self):
        taskMgr.add(self.leftTask,'leftTask')
        self.charWalk1l.loop()
        #end left
        
    def leftTask(self,task):
        if self.climbing1 == 0:
            self.playerModel.setH(270)
            self.playerModel.setPos(Vec3(self.playerModel.getX()-self.speed1, self.playerModel.getY(), self.playerModel.getZ()))
        return Task.cont
        
    def right(self):
        taskMgr.add(self.rightTask,'rightTask')
        self.charWalk1r.loop()
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
            j = ProjectileInterval(self.playerModel, startPos = self.playerModel.getPos(), startVel = Point3(5,0,30), duration = 2.0)
            j.start()
            taskMgr.doMethodLater(2,self.jumpTask,"jumpTask")
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
        self.charWalk1r.pause()
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
        self.charWalk1l.pause()
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
        self.charWalk2l.loop()
    #end left

    def leftTask2(self,task):
        if self.climbing2 == 0:
            self.playerModel2.setH(0)
            self.playerModel2.setPos(Vec3(self.playerModel2.getX()-self.speed2, self.playerModel2.getY(), self.playerModel2.getZ()))
        return Task.cont

    def right2(self):
        taskMgr.add(self.rightTask2,'rightTask2')
        self.charWalk2r.loop()
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
            j = ProjectileInterval(self.playerModel2, startPos = self.playerModel2.getPos(), startVel = Point3(3,0,30), duration = 2.0)
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
        self.charWalk2r.pause()
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
        self.charWalk2l.pause()
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
    
    def setupCollisions(self):
	self.cHandler = PhysicsCollisionHandler()
        #self.cHandler.setInPattern("ate-%in")
        self.cHandler.addInPattern('%fn-into-%in')
	#self.cHandler2.addInPattern('%fn-into-%in')         
        self.cHandler.setAgainPattern('%fn-again-%in')          
        self.cHandler.setOutPattern('%fn-outof-%in')        
        self.cTrav = CollisionTraverser()
	#self.cTrav2 = CollisionTraverser()
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
        #print radius, radiusB
        cNode.addSolid(cSphere)
        cNode.addSolid(cSphereB)
        cNodePath = self.playerModel.attachNewNode(cNode)
        cNodePath.show()
        
        Node=NodePath(PandaNode("PhysicsNode"))
        Node.reparentTo(render)
        self.an1=ActorNode("player1-physics")
        self.anp=Node.attachNewNode(self.an1)
        base.physicsMgr.attachPhysicalNode(self.an1)
        self.playerModel.reparentTo(self.anp)
	#self.anp.reparentTo(self.playerModel)
	
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
        #print radius2, radius2B
        cNode2.addSolid(cSphere2)
        cNode2.addSolid(cSphere2B)
        cNodePath2 = self.playerModel2.attachNewNode(cNode2)
        cNodePath2.show()
        
        Node2=NodePath(PandaNode("PhysicsNode"))
        Node2.reparentTo(render)
        self.an2=ActorNode("player2-physics")
        self.anp2=Node2.attachNewNode(self.an2)
        base.physicsMgr.attachPhysicalNode(self.an2)
        self.playerModel2.reparentTo(self.anp2)
        #self.anp2.reparentTo(self.playerModel2)
	
        gravityFN=ForceNode('world-forces')
        gravityFNP=render.attachNewNode(gravityFN)
        gravityForce=LinearVectorForce(0,0,-9.8) #gravity acceleration
        gravityFN.addForce(gravityForce)
        
        base.physicsMgr.addLinearForce(gravityForce)
	self.an1.getPhysicsObject().setMass(15)
	self.an2.getPhysicsObject().setMass(15)
	gravityForce.setMassDependent(1)
        
        self.cHandler.addCollider(cNodePath, self.anp)
        self.cHandler.addCollider(cNodePath2, self.anp2)
        self.cTrav.addCollider(cNodePath,self.cHandler)
        self.cTrav.addCollider(cNodePath2,self.cHandler)
        self.cTrav.addCollider(cNodePath,self.cHandler)
        self.cTrav.addCollider(cNodePath2,self.cHandler)
	#self.cTrav.addCollider(cNodePath,self.cHandler2)
        #self.cTrav.addCollider(cNodePath2,self.cHandler2)
        #self.cTrav2.addCollider(cNodePath,self.cHandler2)
        #self.cTrav2.addCollider(cNodePath2,self.cHandler2)
	
	#cHandler2 = CollisionHandlerEvent()
	#cHandler2.addInPattern('%fn-into-%in')
	#self.cTrav.addCollider(cNodePath1,cHandler2)
        #self.cTrav.addCollider(cNodePath2,cHandler2)
	
        for i in range(self.ballNum+1):
            boundsB = self.ball[i].getChild(0).getBounds()
            centerB = boundsB.getCenter()
            radiusB = boundsB.getRadius()*0.65
            cSphereB = CollisionSphere(centerB,radiusB)
            cNodeB = CollisionNode("ball")
            cNodeB.addSolid(cSphereB)
            cNodePathB = self.ball[i].attachNewNode(cNodeB)
	    #self.cTrav.addCollider(cNodePathB,self.cHandler)

            #cNodePathB.show()
	
	self.accept("player1-into-ball",self.acquire1)
	#self.accept("ball-into-player1",self.acquire1)
	self.accept("player2-into-ball",self.acquire2)
	#self.accept("ball-into-player2",self.acquire2)
	#self.accept( 'player1-into2-platform', self.wall1)
        #self.accept( 'player2-into2-platform', self.wall2)
        
    def wall1(self,cEntry):
	self.an1.getPhysicsObject().setVelocity(Vec3(0,0,0))
	
    def wall2(self,cEntry):
	self.an2.getPhysicsObject().setVelocity(Vec3(0,0,0))
	
    def player1Wins(self,cEntry):
	if self.player2Invincible == 0:
		self.player1Score+=10
		self.reset()
	
    def player2Wins(self,cEntry):
	if self.player1Invincible == 0:
		self.player2Score+=10
		self.reset()
		
    def acquire1(self,cEntry):
	self.playerModel.setY(0)
	if str(cEntry.getIntoNodePath().getParent()) == "render/sawball":
	    self.player1Weapon = "saw"
	    saw = loader.loadModel("models/gamedev/saw")
	    saw.setScale(2.5)
	    self.jNP.getChildren().detach()
	    saw.reparentTo(self.jNP)
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/moltovball":
	    self.player1Weapon = "molotov"
	    molo = loader.loadModel("models/gamedev/moltov")
	    molo.setScale(2.5)
	    #self.jNP = self.playerModel.exposeJoint(None,"modelRoot","ikHandle2")
	    self.jNP.getChildren().detach()
	    molo.reparentTo(self.jNP)
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/grenadeball":
	    self.player1Weapon = "grenade"
	    gren = loader.loadModel("models/gamedev/grenade")
	    gren.setScale(2.5)
	    #self.jNP = self.playerModel.exposeJoint(None,"modelRoot","ikHandle2")
	    self.jNP.getChildren().detach()
	    gren.reparentTo(self.jNP)
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/pogo": #done
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "jump"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/golden": #done
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "speedUp"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/crystalball":
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "icestage"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/fireball": #done
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "meteo"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/blackball": #done
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "blind"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/translucent":
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "invis"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/superball": #done
	    self.jNP.getChildren().detach()
	    self.player1Weapon = "invincible"
	    self.acceptOnce("e",self.useWeapon1)
	    self.acceptOnce("q",self.useWeapon1)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/death": #done
	    self.jNP.getChildren().detach()
	    if self.player1Invincible == 0:
		self.player2Deaths+= 1
		self.reset()
	
	cEntry.getIntoNodePath().getParent().removeNode()
		
	#Drop a New Ball
	self.ballNum+=1
	z=random.randint(1,2)
	if z ==1:
		z=-1
	else:
		z=1
	self.movement.append(Vec3(random.random()*z,0,random.random()*z))
	weapBalls.define(self.ball,self.ballNum,render)
	
	boundsB = self.ball[self.ballNum].getChild(0).getBounds()
	centerB = boundsB.getCenter()
	radiusB = boundsB.getRadius()*.65
	cSphereB = CollisionSphere(centerB,radiusB)
	cNodeB = CollisionNode("ball")
	cNodeB.addSolid(cSphereB)
	cNodePathB = self.ball[self.ballNum].attachNewNode(cNodeB)
		
    def acquire2(self,cEntry):
	if str(cEntry.getIntoNodePath().getParent()) == "render/sawball":
	    self.player2Weapon = "saw"
	    saw = loader.loadModel("models/gamedev/saw")
	    saw.setScale(2.5)
	    self.jNP2.getChildren().detach()
	    saw.reparentTo(self.jNP2)
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/moltovball":
	    self.player2Weapon = "molotov"
	    molo = loader.loadModel("models/gamedev/moltov")
	    molo.setScale(2.5)
	    #self.jNP = self.playerModel.exposeJoint(None,"modelRoot","ikHandle2")
	    self.jNP.getChildren().detach()
	    molo.reparentTo(self.jNP)
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/grenadeball":
	    self.player2Weapon = "grenade"
	    gren = loader.loadModel("models/gamedev/grenade")
	    gren.setScale(2.5)
	    #self.jNP = self.playerModel.exposeJoint(None,"modelRoot","ikHandle2")
	    self.jNP.getChildren().detach()
	    gren.reparentTo(self.jNP)
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/pogo": #done
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "jump"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/golden": #done
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "speedUp"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/crystalball":
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "icestage"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/fireball": #done
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "meteo"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/blackball": #done
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "blind"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/translucent":
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "invis"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/superball": #done
	    self.jNP.getChildren().detach()
	    self.player2Weapon = "invincible"
	    self.acceptOnce("e",self.useWeapon2)
	    self.acceptOnce("q",self.useWeapon2)
	elif str(cEntry.getIntoNodePath().getParent()) == "render/death": #done
	    self.jNP.getChildren().detach()
	    if self.player2Invincible == 0:
		self.player1Score+=3
		self.reset()
	
	cEntry.getIntoNodePath().getParent().removeNode()
		
	#Drop a New Ball
	self.ballNum+=1
	z=random.randint(1,2)
	if z ==1:
		z=-1
	else:
		z=1
	self.movement.append(Vec3(random.random()*z,0,random.random()*z))
	weapBalls.define(self.ball,self.ballNum,render)
	
	boundsB = self.ball[self.ballNum].getChild(0).getBounds()
	centerB = boundsB.getCenter()
	radiusB = boundsB.getRadius()*.65
	cSphereB = CollisionSphere(centerB,radiusB)
	cNodeB = CollisionNode("ball")
	cNodeB.addSolid(cSphereB)
	cNodePathB = self.ball[self.ballNum].attachNewNode(cNodeB)

    def useWeapon1(self):
	if self.player1Weapon == "meteo":
		fireRain = Sequence(Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), 
		Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain))
		fireRain.start()
	elif self.player1Weapon == "jump":
		self.playerModel.detachNode()
		self.playerModel.reparentTo(render)
		angle = (self.playerModel.getH())*math.pi/180.0
		ProjectileInterval(self.playerModel, startPos = Point3(self.playerModel.getPos()),startVel = Point3(math.sin(angle)*30,0,100), duration= 4.0).start()
	elif self.player1Weapon == "speedUp":
		self.speed1 = 6
		taskMgr.doMethodLater(5,self.restoreSpeedBG,"restoreStuff")
	elif self.player1Weapon == "blind":
		camera.setPos(Vec3(-50,0,0))
		taskMgr.doMethodLater(5,self.restoreCamera,"restoreCamera")
	elif self.player1Weapon == "invincible":
		self.player1Invincible = 1
		taskMgr.doMethodLater(5,self.notInvince1,"mortal1")
	elif self.player1Weapon == "grenade":
		self.jNP.getChildren().detach()
		gren = loader.loadModel("models/gamedev/grenade")
		gren.setScale(2.5)
		gren.reparentTo(render)
		angle = (self.playerModel.getH())*math.pi/180.0
		ProjectileInterval(gren, startPos = Point3(self.playerModel.getPos()),startVel = Point3(math.sin(angle)*30,0,10), endZ = -50).start()
		if gren.getZ() == -50:
			gren.removeNode()
		cHandler = CollisionHandlerEvent()
		cHandler.addInPattern('%fn-into-%in')
		boundsB = gren.getChild(0).getBounds()
		centerB = boundsB.getCenter()
		radiusB = boundsB.getRadius()*0.65
		cSphereB = CollisionSphere(centerB,radiusB)
		cNodeB = CollisionNode("grenade")
		cNodeB.addSolid(cSphereB)
		cNodePathB = gren.attachNewNode(cNodeB)
		self.cTrav.addCollider(cNodePathB,cHandler)
		
		self.acceptOnce("grenade-into-platform",self.explode)
		
	elif self.player1Weapon == "molotov":
		self.jNP.getChildren().detach()
	elif self.player1Weapon == "saw":
		self.jNP.getChildren().detach()
	elif self.player1Weapon == "invis":
		self.jNP.getChildren().detach()
		self.playerModel2.hide()
		taskMgr.doMethodLater(4.0,self.showPlayer,"showPlayer")
	elif self.player1Weapon == "icestage":
		self.jNP.getChildren().detach()
		self.speed1 = 6
		self.speed2 = 6
		self.background.detachNode()
		self.background2.reparentTo(render)
		taskMgr.doMethodLater(5,self.restoreSpeedBG,"restoreStuff")
		
    def restoreSpeedBG(self,task):
	self.speed1 = 3
	self.speed2 = 3
	self.background2.detachNode()
	self.background.reparentTo(render)
	
    def showPlayer(self,task):
	self.playerModel.show()
	self.playerModel2.show()
	
    def useWeapon2(self):
	if self.player2Weapon == "meteo":
		fireRain = Sequence(Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), 
		Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain), Wait(.5), Func(self.rain))
		fireRain.start()
	elif self.player2Weapon == "jump":
		angle = self.playerModel2.getH()/90
		ProjectileInterval(self.playerModel2, startPos = Point3(self.playerModel2.getPos()),startVel = Point3(angle*30,0,100), endZ = self.playerModel2.getZ()).start()
	elif self.player2Weapon == "speedUp":
		self.speed2 = 6
	elif self.player2Weapon == "blind":
		camera.setPos(Vec3(-50,0,0))
		taskMgr.doMethodLater(5,self.restoreCamera,"restoreCamera")
	elif self.player2Weapon == "invincible":
		self.player2Invincible = 1
		taskMgr.doMethodLater(5,self.notInvince2,"mortal2")
	elif self.player2Weapon == "grenade":
		self.jNP2.getChildren().detach()
		gren = loader.loadModel("models/gamedev/grenade")
		gren.setScale(2.5)
		gren.reparentTo(render)
		angle = (self.playerModel2.getH())*math.pi/180.0
		ProjectileInterval(gren, startPos = Point3(self.playerModel2.getPos()),startVel = Point3(math.sin(angle)*30,0,10), endZ = -50).start()
		if gren.getZ() == -50:
			gren.removeNode()
		cHandler = CollisionHandlerEvent()
		cHandler.addInPattern('%fn-into-%in')
		boundsB = gren.getChild(0).getBounds()
		centerB = boundsB.getCenter()
		radiusB = boundsB.getRadius()*0.65
		cSphereB = CollisionSphere(centerB,radiusB)
		cNodeB = CollisionNode("grenade")
		cNodeB.addSolid(cSphereB)
		cNodePathB = gren.attachNewNode(cNodeB)
		self.cTrav.addCollider(cNodePathB,cHandler)
		
		self.acceptOnce("grenade-into-platform",self.explode)
		
	elif self.player2Weapon == "molotov":
		self.jNP.getChildren().detach()
	elif self.player2Weapon == "saw":
		self.jNP.getChildren().detach()
	elif self.player2Weapon == "invis":
		self.jNP.getChildren().detach()
		self.playerModel1.hide()
		taskMgr.doMethodLater(4.0,self.showPlayer,"showPlayer")
	elif self.player2Weapon == "icestage":
		self.jNP2.getChildren().detach()
		self.speed1 = 6
		self.speed2 = 6
		self.background.detachNode()
		self.background2.reparentTo(render)
		taskMgr.doMethodLater(5,self.restoreSpeedBG,"restoreStuff")
		
    def rain(self):
	    meteoBall = Actor("models/gamedev/fireball")
	    meteoBall.reparentTo(render)
	    meteoBall.setScale(2)
	    meteoBall.setH(-15)
	    boundsB = meteoBall.getChild(0).getBounds()
            centerB = boundsB.getCenter()
            radiusB = boundsB.getRadius()*0.65
            cSphereB = CollisionSphere(centerB,radiusB)
            cNodeB = CollisionNode("meteor")
            cNodeB.addSolid(cSphereB)
            cNodePathB = meteoBall.attachNewNode(cNodeB)
	    #cNodePathB.show()
	    
	    ProjectileInterval(meteoBall, startPos = Point3(random.randint(15,211),0,170),startVel = Point3(-12,0,0), endZ = -50).start()
	    
	    cHandler = CollisionHandlerEvent()
	    cHandler.addInPattern('%fn-into-%in')
	    self.cTrav.addCollider(cNodePathB,cHandler)
	    self.accept("meteor-into-player1",self.player2Wins)
	    self.accept("meteor-into-player2",self.player1Wins)
	    
    def showBalls(self,task):
        for i in self.ball:
            i.show()
     
    def notInvince1(self,task):
	self.player1Invincible = 0
	
    def notInvince2(self,task):
        self.player2Invincible = 0

    def restoreCamera(self,task):
        camera.setPosHpr(Vec3(98,-390,90), Vec3(0,-5,0))
        
    def switch(self,task):
        self.environment.setColor(0,1,0.3)
        
    def colliding1( self, collEntry ): # accept a collision entry argument    
        if self.ignoreColl == 0:
            self.player1IsColliding = 1 # we are colliding        
            self.stopWalk( ) # pause all walking animation and movement        
            disp = ( collEntry.getSurfacePoint( render ) - collEntry.getInteriorPoint( render ) )
            newPos = self.playerModel2.getPos( ) + disp # get new position
            self.playerModel2.setPos( newPos ) # and set it to tiny's position
        # end colliding        
        
    def notColliding1( self, collEntry ): 
        self.player1IsColliding = 0    
        
    def colliding2( self, collEntry ): # accept a collision entry argument 
        if self.ignoreColl == 0:
            self.player2IsColliding = 1 # we are colliding        
            self.stopWalk2( ) # pause all walking animation and movement               
            disp = ( collEntry.getSurfacePoint( render ) - collEntry.getInteriorPoint( render ) )
            newPos = self.playerModel2B.getPos( ) + disp # get new position
            self.playerModel2B.setPos( newPos ) # and set it to tiny's position
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
        self.timer.detachNode()
        self.timer = OnscreenText("%d" % (self.gameLen-globalClock.getRealTime(),), pos = (98,145), scale = 18.0)
        self.timer.setColor(1,1,1)
        self.timer.reparentTo(render)
        return Task.cont
    
    def ballMovementTask(self,task):
	self.anp.setY(0)
	self.anp2.setY(0)
	for i in range(self.ballNum+1):
		if i < len(self.ball):
			if self.ball[i].getX() > 234 or self.ball[i].getX() < -38 or self.ball[i].getZ() < -10 or self.ball[i].getZ() > 132:
				self.ball[i].setPos(self.ball[i].getPos()/1.005)
				z=random.randint(1,2)
				if z ==1:
					z=-1
				else:
					z=1
				self.movement[i]=Vec3(random.random()*z,0,random.random()*z)
			else:
				self.ball[i].setPos(self.ball[i].getPos()+self.movement[i])
	return Task.cont
	
    def fire(self):
        
        self.fire = ParticleEffect()
        
        self.fire.reset()
        self.fire.setPos(0.000, 0.000, 0.000)
        self.fire.setHpr(0.000, 0.000, 0.000)
        self.fire.setScale(10.000, 10.000, 10.000)
        p0 = Particles('particles-1')
        # Particles parameters
        p0.setFactory("PointParticleFactory")
        p0.setRenderer("SpriteParticleRenderer")
        p0.setEmitter("DiscEmitter")
        p0.setPoolSize(1024)
        p0.setBirthRate(0.0200)
        p0.setLitterSize(10)
        p0.setLitterSpread(0)
        p0.setSystemLifespan(1200.0000)
        p0.setLocalVelocityFlag(1)
        p0.setSystemGrowsOlderFlag(0)
        # Factory parameters
        p0.factory.setLifespanBase(2.0000)
        p0.factory.setLifespanSpread(0.0000)
        p0.factory.setMassBase(1.0000)
        p0.factory.setMassSpread(0.0000)
        p0.factory.setTerminalVelocityBase(400.0000)
        p0.factory.setTerminalVelocitySpread(0.0000)
        # Point factory parameters
        # Renderer parameters
        p0.renderer.setAlphaMode(BaseParticleRenderer.PRALPHAOUT)
        p0.renderer.setUserAlpha(0.22)
        # Sprite parameters
        p0.renderer.addTextureFromFile('models/gamedev/sparkle.png')
        p0.renderer.setColor(Vec4(1.00, 1.00, 1.00, 1.00))
        p0.renderer.setXScaleFlag(1)
        p0.renderer.setYScaleFlag(1)
        p0.renderer.setAnimAngleFlag(0)
        p0.renderer.setInitialXScale(0.5000)
        p0.renderer.setFinalXScale(2.0000)
        p0.renderer.setInitialYScale(1.0000)
        p0.renderer.setFinalYScale(2.0000)
        p0.renderer.setNonanimatedTheta(0.0000)
        p0.renderer.setAlphaBlendMethod(BaseParticleRenderer.PPNOBLEND)
        p0.renderer.setAlphaDisable(0)
        # Emitter parameters
        p0.emitter.setEmissionType(BaseParticleEmitter.ETRADIATE)
        p0.emitter.setAmplitude(1.0000)
        p0.emitter.setAmplitudeSpread(0.0000)
        p0.emitter.setOffsetForce(Vec3(0.0000, 0.0000, 3.0000))
        p0.emitter.setExplicitLaunchVector(Vec3(1.0000, 0.0000, 0.0000))
        p0.emitter.setRadiateOrigin(Point3(0.0000, 0.0000, 0.0000))
        # Disc parameters
        p0.emitter.setRadius(0.5000)
        self.fire.addParticles(p0)
        
        self.fire.setPos(self.playerModel2.getPos())
        
        t = Sequence(Func(self.fire.start, render, render),Wait(20),Func(self.cleanFire))
        t.start()
 
    def cleanFire(self):
        self.fire.cleanup()

    def explode(self,cEntry):

        self.explosion = ParticleEffect()
        
        self.explosion.reset()
        self.explosion.setPos(cEntry.getIntoNodePath().getParent().getPos())
        self.explosion.setHpr(0.000, 0.000, 0.000)
        self.explosion.setScale(10.000, 10.000, 10.000)
        p0 = Particles('particles-1')
        # Particles parameters
        p0.setFactory("PointParticleFactory")
        p0.setRenderer("LineParticleRenderer")
        p0.setEmitter("SphereVolumeEmitter")
        p0.setPoolSize(10000)
        p0.setBirthRate(0.0500)
        p0.setLitterSize(10000)
        p0.setLitterSpread(0)
        p0.setSystemLifespan(2.0000)
        p0.setLocalVelocityFlag(1)
        p0.setSystemGrowsOlderFlag(1)
        # Factory parameters
        p0.factory.setLifespanBase(2.0000)
        p0.factory.setLifespanSpread(0.0000)
        p0.factory.setMassBase(.5000)
        p0.factory.setMassSpread(0.0500)
        p0.factory.setTerminalVelocityBase(400.0000)
        p0.factory.setTerminalVelocitySpread(0.0000)
        # Point factory parameters
        # Renderer parameters
        p0.renderer.setAlphaMode(BaseParticleRenderer.PRALPHAOUT)
        p0.renderer.setUserAlpha(1.00)
        # Line parameters
        p0.renderer.setHeadColor(Vec4(1.00, 0.00, 0.00, 1.00))
        p0.renderer.setTailColor(Vec4(1.00, 1.00, 0.00, 1.00))
        p0.renderer.setLineScaleFactor(3.00)
        # Emitter parameters
        p0.emitter.setEmissionType(BaseParticleEmitter.ETRADIATE)
        p0.emitter.setAmplitude(10.0000)
        p0.emitter.setAmplitudeSpread(0.0000)
        p0.emitter.setOffsetForce(Vec3(0.0000, 0.0000, -0.4930))
        p0.emitter.setExplicitLaunchVector(Vec3(1.0000, 0.0000, 0.0000))
        p0.emitter.setRadiateOrigin(Point3(0.0000, 0.0000, 0.0000))
        # Sphere Volume parameters
        p0.emitter.setRadius(0.5000)
        self.explosion.addParticles(p0)
        f0 = ForceGroup('gravity')
        # Force parameters
        self.explosion.addForceGroup(f0)
        
	cHandler = CollisionHandlerEvent()
	cHandler.addInPattern('%fn-into-%in')
	cSphereB = CollisionSphere(cEntry.getIntoNodePath().getParent().getPos(),1)
	cNodeB = CollisionNode("explosion")
	cNodeB.addSolid(cSphereB)
	cNodePathB = self.explosion.attachNewNode(cNodeB)
	self.cTrav.addCollider(cNodePathB,cHandler)
	cNodePathB.show()
        
	self.accept("player1-into-explosion",self.player2Wins)
	self.accept("player2-into-explosion",self.player1Wins)
        #f.reparentTo(self.playerModel)
        #self.explosion.setPos(self.playerModel.getPos())

        t = Sequence(Func(self.explosion.start, render, render),Wait(2),Func(self.cleanExplo))
        t.start()
	cEntry.getFromNodePath().getParent().removeNode()
        
    def cleanExplo(self):
        self.explosion.cleanup()

    def endGame(self,task):
        taskMgr.removeTasksMatching('returnSpeedsToNormal')
        taskMgr.removeTasksMatching('restoreCamera')
	taskMgr.removeTasksMatching('clockTask')
	taskMgr.removeTasksMatching('ballMoveTask')
	
	self.music.stop()

        self.music3  = loader.loadMusic("models/gamedev/CSTAR.mp3")
        self.music3.play()
        
        self.speed1 = 0
        self.speed2 = 0

    def getScores(self):
	return (self.player1Score, self.player2Score)
		
    def getGameLen(self):
	return self.gameLen
		
    def stopMusic(self):
	self.music3.stop()
	
    def destroy(self):
	self.playerModel.detachNode()
	self.playerModel2.detachNode()
	self.background.destroy()
	self.lava.detachNode()
	self.ladder.detachNode()
	self.ladder2.detachNode()
	
	for i in range(self.ballNum+1):
	    self.ball[i].detachNode()
	    
    def stopMusic(self):
        self.music3.stop()
        
#world = Lvl03()
#world.start()
#run()