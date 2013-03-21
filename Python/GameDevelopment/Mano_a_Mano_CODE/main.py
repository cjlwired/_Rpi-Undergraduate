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
from LVL01 import Lvl01
from LVL02 import Lvl02
from LVL03 import Lvl03
from direct.gui.OnscreenImage import OnscreenImage
from direct.gui.OnscreenText import OnscreenText
from direct.gui.DirectGui import *

class World(DirectObject):
	def __init__(self):
		
		base.disableMouse()
		
		camera.setPosHpr(Vec3(0,-20,0), Vec3(0,0,0))
		
		self.totalscore1 = 0
		self.totalscore2 = 0
		
		self.lvl01score1 = 0
		self.lvl01score2 = 0
		
		self.lvl02score1 = 0
		self.lvl02score2 = 0
		
		self.lvl03score1 = 0
		self.lvl03score2 = 0
		
		self.initGame()
	
	def initGame(self):
		
		#base.openWindow()
		
		#self.Lvl01Window = base.openWindow(size=[500,500])
		#self.Lvl01Window.setActive(1)
		
		self.totalscore1 = 0
		self.totalscore2 = 0
		
		self.lvl01score1 = 0
		self.lvl01score2 = 0
		
		self.lvl02score1 = 0
		self.lvl02score2 = 0
		
		self.lvl03score1 = 0
		
		self.titleMusic = loader.loadMusic("models/gamedev/AP.mp3")
		self.titleMusic.play()
		
		self.titleScreen = DirectFrame (image = 'models/gamedev/title_screen.JPG')
		self.titleScreen['frameSize'] = (0,0,0,0)
		self.titleScreen['image_scale'] = (1.5,1,1)
		self.titleScreen['image_pos'] = (0,-20,0)
		
		# Initialize all buttons here, setting all button geometry to their respective positions, sizes, and setting all opaqueness to 0
		
		self.clickToStart = DirectButton(scale = 1, pos = (0,0,-.275), command = self.setupLvl01, frameColor = (1,1,1,0))
		self.clickToStart.setScale(4,1,1)
		
		self.clickForCredits = DirectButton(scale = 1, pos = (0,0,-.525), command = self.setupCredits, frameColor = (1,1,1,0))
		self.clickForCredits.setScale(3.5,1,1)
		
		self.clickForExit = DirectButton(scale = 1, pos = (-.215,0,-.775), command = sys.exit, frameColor = (1,1,1,0))
		self.clickForExit.setScale(3.35,1,1)
		
	def setupCredits(self):
		
		self.titleScreen.destroy()
		self.clickToStart.destroy()
		self.clickForCredits.destroy()
		self.clickForExit.destroy()
		
		self.titleMusic.stop()
		
		self.creditMusic = loader.loadMusic("models/gamedev/CS.mp3")
		self.creditMusic.play()
		
		self.creditScreen = DirectFrame (image = 'models/gamedev/credits.jpg')
		self.creditScreen['frameSize'] = (0,0,0,0)
		self.creditScreen['image_scale'] = (7.65,1,5.40)
		self.creditScreen['image_pos'] = (0,.1,0)
		
		self.creditScreen.reparentTo(render)
		
		self.clickToStart = DirectButton(text = ("Return to Main Menu"),scale = .1, pos = (.85,0,-.85), command = self.endCredits)
		
		
	def endCredits(self):
		
		self.creditScreen.destroy()
		self.clickToStart.destroy()
		
		self.creditMusic.stop()
		
		base.restart()
		
		self.initGame()
	
	# DEFINITIONS FOR STAGE 1
	
	def setupLvl01(self):
		
		self.titleScreen.destroy()
		self.clickToStart.destroy()
		self.clickForCredits.destroy()
		self.clickForExit.destroy()
		
		self.titleMusic.stop()
		
		self.instructionMusic = loader.loadMusic("models/gamedev/CV.mp3")
		self.instructionMusic.play()
		
		self.instruction01 = DirectFrame(image = 'models/gamedev/lvl1_infoscreen.jpg')
		self.instruction01['frameSize'] = (0,0,0,0)
		self.instruction01['image_scale'] = (7.775,1,5.60)
		self.instruction01['image_pos'] = (0,1,0)
		
		self.instruction01.reparentTo(render)
		
		self.clickToStart = DirectButton(text = ("Click to Start!"),scale = .1, pos = (-.85,0,-.85), command = self.startLvl01, frameColor = (0,0,0,0))
	
	def startLvl01(self):
		
		self.instruction01.destroy()
		self.clickToStart.destroy()
		self.instructionMusic.stop()
		
		self.stage1 = Lvl01()
		self.stage1.start()
		
		taskMgr.doMethodLater(self.stage1.getGameLen() + 5,self.endLvl01,'endLvl01')
		
	def endLvl01 (self,task):
		
		base.makeCamera(base.win, displayRegion = (0, 1, 0, 1))
		
		self.totalScore01 = self.stage1.getScores()
		
		self.lvl01score1 = self.totalScore01[0]
		self.lvl01score2 = self.totalScore01[1]
		
		self.totalscore1 += self.lvl01score1
		self.totalscore2 += self.lvl01score2
		
		self.stage1.destroy()
		
		# Normal score screen display code display code
		
		self.scoreScreen = DirectFrame(image = 'models/gamedev/score.JPG')
		self.scoreScreen['frameSize'] = (0,0,0,0)
		self.scoreScreen['image_scale'] = (22.5,15,15)
		self.scoreScreen['image_pos'] = (0,5,-900)
	
		self.points1a = OnscreenText(text = str(self.lvl01score1),pos = (-11.75,-894.75),scale = 5.0)
		self.points1b = OnscreenText(text = str(self.lvl01score2),pos = (11.15,-894.75),scale = 5.0)
		
		self.points2a = OnscreenText(text = str(self.lvl02score1),pos = (-11.75,-901.75),scale = 5.0)
		self.points2b = OnscreenText(text = str(self.lvl02score2),pos = (11.15,-901.75),scale = 5.0)
		
		self.points3a = OnscreenText(text = str(self.lvl03score1),pos = (-11.75,-908.5),scale = 5.0)
		self.points3b = OnscreenText(text = str(self.lvl03score2),pos = (11.15,-908.5),scale = 5.0)

		self.points1a.setColor(1,1,1)
		self.points1b.setColor(1,1,1)
		
		self.points2a.setColor(1,1,1)
		self.points2b.setColor(1,1,1)
		
		self.points3a.setColor(1,1,1)
		self.points3b.setColor(1,1,1)
		
		self.points1a.reparentTo(render)
		self.points1b.reparentTo(render)
		
		self.points2a.reparentTo(render)
		self.points2b.reparentTo(render)
		
		self.points3a.reparentTo(render)
		self.points3b.reparentTo(render)
		
		self.scoreScreen.reparentTo(render)
			
		camera.setPosHpr(Vec3(0,-51,-900), Vec3(0,0,0))
		
		self.progressLvl02 = DirectButton(text = ("Click for Stage 2"),scale = .1, pos = (-.85,0,-.85), command = self.setupLvl02)
		
	# DEFINITIONS FOR STAGE 2
		
	def setupLvl02(self):
		
		# Uncomment once LVL01 works! #
		
		self.scoreScreen.destroy()
		self.points1a.destroy()
		self.points1b.destroy()
		self.points2a.destroy()
		self.points2b.destroy()
		self.points3a.destroy()
		self.points3b.destroy()
		self.progressLvl02.destroy()
		
		self.stage1.stopMusic()
		
		self.instructionMusic = loader.loadMusic("models/gamedev/CV.mp3")
		self.instructionMusic.play()
		
		self.instruction02 = DirectFrame(image = 'models/gamedev/lvl2_infoscreen.jpg')
		self.instruction02['frameSize'] = (0,0,0,0)
		self.instruction02['image_scale'] = (7.775,1,5.60)
		self.instruction02['image_pos'] = (0,1,0)
		
		self.instruction02.reparentTo(render)
		
		camera.setPosHpr(Vec3(0,-20,0), Vec3(0,0,0))
		
		self.clickToStart = DirectButton(text = ("Click to Start!"),scale = .1, pos = (-.85,0,-.85), command = self.startLvl02, frameColor = (0,0,0,0))
	
	def startLvl02(self):
		
		self.instruction02.destroy()
		self.clickToStart.destroy()
		self.instructionMusic.stop()
		
		self.stage2 = Lvl02()
		self.stage2.start()
		
		taskMgr.doMethodLater(self.stage2.getGameLen() + 5,self.endLvl02,'endLvl02')
		
	def endLvl02 (self,task):
		
		self.totalScore02 = self.stage2.getScores()
		
		self.lvl02score1 = self.totalScore02[0]
		self.lvl02score2 = self.totalScore02[1]
		
		self.totalscore1 += self.lvl02score1
		self.totalscore2 += self.lvl02score2
		
		self.stage2.destroy()
		
		# Normal score screen display code display code
		
		self.scoreScreen = DirectFrame(image = 'models/gamedev/score.JPG')
		self.scoreScreen['frameSize'] = (0,0,0,0)
		self.scoreScreen['image_scale'] = (22.5,15,15)
		self.scoreScreen['image_pos'] = (0,1,100)
	
		self.points1a = OnscreenText(text = str(self.lvl01score1),pos = (-12.3,105.5),scale = 5.0)
		self.points1b = OnscreenText(text = str(self.lvl01score2),pos = (11.8,105.5),scale = 5.0)
		
		self.points2a = OnscreenText(text = str(self.lvl02score1),pos = (-12.3,98.25),scale = 5.0)
		self.points2b = OnscreenText(text = str(self.lvl02score2),pos = (11.8,98.25),scale = 5.0)
		
		self.points3a = OnscreenText(text = str(self.lvl03score1),pos = (-12.3,91.0),scale = 5.0)
		self.points3b = OnscreenText(text = str(self.lvl03score2),pos = (11.8,91.0),scale = 5.0)

		self.points1a.setColor(1,1,1)
		self.points1b.setColor(1,1,1)
		
		self.points2a.setColor(1,1,1)
		self.points2b.setColor(1,1,1)
		
		self.points3a.setColor(1,1,1)
		self.points3b.setColor(1,1,1)
		
		self.points1a.reparentTo(render)
		self.points1b.reparentTo(render)
		
		self.points2a.reparentTo(render)
		self.points2b.reparentTo(render)
		
		self.points3a.reparentTo(render)
		self.points3b.reparentTo(render)
		
		self.scoreScreen.reparentTo(render)
			
		camera.setPosHpr(Vec3(0,-55,100), Vec3(0,0,0))
		
		self.clickForStage3 = DirectButton(text = ("Click for Stage 3"),scale = .1, pos = (-.85,0,-.85), command = self.setupLvl03)
	
	# DEFINITIONS FOR STAGE 3
		
	def setupLvl03(self):
		
	# Comment out if you want to begin from LVL03 #
		
		self.scoreScreen.destroy()
		self.points1a.destroy()
		self.points1b.destroy()
		self.points2a.destroy()
		self.points2b.destroy()
		self.points3a.destroy()
		self.points3b.destroy()
		self.clickForStage3.destroy()
		
		self.stage2.stopMusic()
		
		self.instructionMusic = loader.loadMusic("models/gamedev/CV.mp3")
		self.instructionMusic.play()
		
		camera.setPosHpr(Vec3(0,-10,0), Vec3(0,0,0))
		
		self.instruction03 = DirectFrame(image = 'models/gamedev/lvl3_infoscreen.jpg')
		self.instruction03['frameSize'] = (0,0,0,0)
		self.instruction03['image_scale'] = (4.25,1,3)
		self.instruction03['image_pos'] = (0,1,0)
		
		self.instruction03.reparentTo(render)
		
		self.clickToStart = DirectButton(text = ("Click to Start!"),scale = .1, pos = (-.85,0,-.85), command = self.startLvl03, frameColor = (0,0,0,0))
	
	def startLvl03(self):
		
		self.instruction03.destroy()
		self.clickToStart.destroy()
		self.instructionMusic.stop()
		
		self.stage3 = Lvl03()
		self.stage3.start()
		
		taskMgr.doMethodLater(self.stage3.getGameLen() + 5,self.endLvl03,'endLvl03')
		
	def endLvl03 (self,task):
		
		self.totalScore03 = self.stage3.getScores()
		
		self.lvl03score1 = self.totalScore03[0]
		self.lvl03score2 = self.totalScore03[1]
		
		self.totalscore1 += self.lvl03score1
		self.totalscore2 += self.lvl03score2
		
		self.stage3.destroy()
		
		# Normal score screen display code display code.
		
		self.scoreScreen = DirectFrame(image = 'models/gamedev/score.JPG')
		self.scoreScreen['frameSize'] = (0,0,0,0)
		self.scoreScreen['image_scale'] = (22.5,15,15)
		self.scoreScreen['image_pos'] = (0,1,100)
		
		self.points1a = OnscreenText(text = str(self.lvl01score1),pos = (-12.3,105.5),scale = 5.0)
		self.points1b = OnscreenText(text = str(self.lvl01score2),pos = (11.8,105.5),scale = 5.0)
		
		self.points2a = OnscreenText(text = str(self.lvl02score1),pos = (-12.3,98.25),scale = 5.0)
		self.points2b = OnscreenText(text = str(self.lvl02score2),pos = (11.8,98.25),scale = 5.0)
		
		self.points3a = OnscreenText(text = str(self.lvl03score1),pos = (-12.3,91.0),scale = 5.0)
		self.points3b = OnscreenText(text = str(self.lvl03score2),pos = (11.8,91.0),scale = 5.0)

		self.points1a.setColor(1,1,1)
		self.points1b.setColor(1,1,1)
		
		self.points2a.setColor(1,1,1)
		self.points2b.setColor(1,1,1)
		
		self.points3a.setColor(1,1,1)
		self.points3b.setColor(1,1,1)
		
		self.points1a.reparentTo(render)
		self.points1b.reparentTo(render)
		
		self.points2a.reparentTo(render)
		self.points2b.reparentTo(render)
		
		self.points3a.reparentTo(render)
		self.points3b.reparentTo(render)
		
		self.scoreScreen.reparentTo(render)
			
		camera.setPosHpr(Vec3(0,-55,100), Vec3(0,0,0))
		
		self.clickToStart = DirectButton(text = ("Final Results"),scale = .1, pos = (-.85,0,-.85), command = self.endGame)
		
	# Display end results
	
	def endGame (self):
		
		self.scoreScreen.destroy()
		self.points1a.destroy()
		self.points1b.destroy()
		self.points2a.destroy()
		self.points2b.destroy()
		self.points3a.destroy()
		self.points3b.destroy()
		self.clickToStart.destroy()
		
		self.stage3.stopMusic()
		
		self.endMusic = loader.loadMusic("models/gamedev/BB.mp3")
		self.endMusic.play()
		
		if (self.totalscore1 > self.totalscore2):
			self.finalScoreScreen = DirectFrame(image = 'models/gamedev/redwin.jpg')
		elif (self.totalscore1 < self.totalscore2):
			self.finalScoreScreen = DirectFrame(image = 'models/gamedev/bluewin.jpg')
		else:
			self.finalScoreScreen = DirectFrame(image = 'models/gamedev/tie.jpg')
			
		self.finalScoreScreen['frameSize'] = (0,0,0,0)
		self.finalScoreScreen['image_scale'] = (24.5,15,15)
		self.finalScoreScreen['image_pos'] = (0,1,100)
		
		self.points1a = OnscreenText(text = str(self.totalscore1),pos = (-15.0,106),scale = 5.0)
		self.points1b = OnscreenText(text = str(self.totalscore2),pos = (14.5,106),scale = 5.0)
		
		self.points1a.setColor(1,1,1)
		self.points1b.setColor(1,1,1)
		
		self.points1a.reparentTo(render)
		self.points1b.reparentTo(render)
		
		self.finalScoreScreen.reparentTo(render)
		
		camera.setPosHpr(Vec3(0,-55,100), Vec3(0,0,0))
		
		self.clickToRestart = DirectButton(text = ("Thanks for playing!"),scale = .1, pos = (-.85,0,-.85), command = sys.exit)
	

world = World()
run()
		