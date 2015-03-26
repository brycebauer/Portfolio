from naoqi import ALProxy
import Tkinter as tk

class Nao:
    def __init__(self, top):
        IP = "sylvester.local"
        #IP = '169.254.258.191'
        self.motion = ALProxy("ALMotion", IP, 9559)
        self.posture = ALProxy("ALRobotPosture", IP, 9559)
        #self.tts = ALProxy("ALTextToSpeech", IP, 9559)

        self.standUp = tk.Button(top, text = "Stand Up", command = self.standTheFUp)
        self.forward = tk.Button(top, text = "Forward", command = self.moveForward)
        self.backward = tk.Button(top, text = "Backward", command = self.moveBackward)
        self.turnRight = tk.Button(top, text = "Turn left", command = self.moveTurnRight)
        self.turnLeft = tk.Button(top, text = "Turn Right", command = self.moveTurnLeft)
        self.shuffleRight = tk.Button(top, text = "Shuffle Left", command = self.moveShuffleRight)
        self.shuffleLeft = tk.Button(top, text = "Shuffle Right", command = self.moveShuffleLeft)
        self.stop = tk.Button(top, text = "Stop", command = self.stopMove)
        self.moveRight = tk.Button(top, text = "Move Right", command = self.moveMoveRight)
        self.moveLeft = tk.Button(top, text = "Move Left", command = self.moveMoveLeft)
        self.kickRight = tk.Button(top, text = "Kick Right", command = self.kickRightLeg)
        self.kickLeft = tk.Button(top, text = "Kick Left", command = self.kickLeftLeg)
        self.lookdown = tk.Button(top, text = "Look Down", command = self.lookdown)
        
        self.standUp.pack()
        self.forward.pack()
        self.backward.pack()
        self.turnRight.pack()
        self.turnLeft.pack()	
        self.shuffleRight.pack()
        self.shuffleLeft.pack()
        self.stop.pack()
        self.kickRight.pack()
        self.kickLeft.pack()
        self.lookdown.pack()

    def lookdown(self):
        print "looking down"
        self.motion.setAngles("HeadPitch", 1.0, 0.1)
        pass
    
    def moveForward(self):
        print "forward"
        self.motion.moveToward(0.5, 0.0, 0.0)
        pass
		
    def moveTurnRight(self):
        print "turn right"
        self.motion.moveToward(0.0, 0.0, 0.2)
        pass
		
    def moveTurnLeft(self):
        print "turn left"
        self.motion.moveToward(0.3, 0.0, -0.2)
        pass
		
    def moveBackward(self):
        print "backward"
        self.motion.moveToward(-0.5, 0.0, 0.0)
        pass
		
    def moveShuffleRight(self):
        print "shuffle right"
        self.motion.moveToward(0.0, 0.3, 0.0)
        pass
		
    def moveShuffleLeft(self):
        print "shuffle left"
        self.motion.moveToward(0.0, -0.3, 0.0)
        pass
		
    def moveMoveRight(self):
        print "move right"
        self.motion.moveToward(0.3, 0.0, 0.2)
        pass
		
    def moveMoveLeft(self):
        print "walking"
        self.motion.moveToward(0.3, 0.0, -0.2)
        pass
		
    def stopMove(self):
        print "walking"
        self.motion.moveToward(0.0, 0.0, 0.0)
        pass

    def sit(self):
        print "Sitting"
        self.posture.goToPosture("Sit", .8)
        pass

    def standTheFUp(self):
        print "standing"
        self.motion.post.stiffnessInterpolation("Body", 1, 0.1)
        print "position " + self.posture.getPostureFamily()
        
        if self.posture.getPostureFamily() == "Standing":
            #why does elmer believe that he is standing when he is crouching?
            print "I am Crouching - stand up now"
            self.posture.goToPosture("Stand", .6)       
        elif self.posture.getPostureFamily() == "Sitting":
            print "I am sitting - stand up now"
            # Choregraphe simplified export in Python.
            #from naoqi import ALProxy
            names = list()
            times = list()
            keys = list()

            names.append("HeadPitch")
            times.append([ 0.60000, 1.12000, 1.60000, 2.24000, 3.00000, 3.76000, 5.04000, 7.20000])
            keys.append([ 0.38907, 0.39349, 0.20306, 0.45788, 0.54516, 0.67355, 0.87886, 1.0])

            names.append("HeadYaw")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.76000, 5.04000, 7.20000])
            keys.append([ 0.00149, -0.30309, -0.37210, -0.45336, -0.56532, -0.26306, -0.00344, -0.00940])

            names.append("LAnklePitch")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ 0.77616, 0.75542, 0.74350, 0.63939, -0.45379, -0.68068, -1.09956, -1.18944, -1.18944, -0.73636])

            names.append("LAnkleRoll")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ -0.05058, -0.00550, 0.02671, -0.15665, -0.39573, -0.08681, -0.10379, 0.01078, -0.01683, -0.08893])

            names.append("LElbowRoll")
            times.append([ 0.60000, 1.12000, 1.56000, 1.92000, 2.20000, 3.00000, 3.40000, 3.76000, 4.36000, 5.04000, 7.20000])
            keys.append([ -1.23170, -1.03128, -0.70442, -0.84983, -0.03491, -0.09355, -0.06146, -0.04087, -0.32652, -0.51540, -0.97613])

            names.append("LElbowYaw")
            times.append([ 0.60000, 1.12000, 1.48000, 2.20000, 3.00000, 3.40000, 3.76000, 4.36000, 5.04000, 7.20000])
            keys.append([ -0.48327, -1.81589, -2.02011, 0.09813, 0.09083, 0.08270, 0.07069, -0.32397, -1.70249, -0.96317])

            #names.append("LHand")
            #times.append([ 0.60000, 1.12000, 1.56000])
            #keys.append([ 0.00032, 0.00116, 0.00126])

            names.append("LHipPitch")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 4.36000, 5.04000, 5.80000, 7.20000])
            keys.append([ -1.57077, -1.57080, -1.57080, -1.57080, -0.82130, -0.59586, -0.02852, -0.40143, -0.69026, -0.75469, -0.73014])

            names.append("LHipRoll")
            times.append([ 0.60000, 1.12000, 1.60000, 2.20000, 2.96000, 3.28000, 3.80000, 5.04000, 5.80000, 7.20000])
            keys.append([ 0.13964, 0.14501, 0.16000, 0.51721, 0.14902, -0.01930, -0.21625, 0.22430, 0.44030, 0.13043])

            names.append("LHipYawPitch")
            times.append([ 0.60000, 1.12000, 1.56000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ -0.67645, -0.65173, -0.75144, -0.49909, -0.64559, -0.85897, -0.43408, -0.28221, -0.17330])

            names.append("LKneePitch")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ 0.72401, 0.95923, 1.19665, 1.67552, 2.11255, 2.11255, 2.11255, 2.00182, 2.11253, 1.61833])

            names.append("LShoulderPitch")
            times.append([ 0.60000, 0.84000, 1.12000, 1.60000, 2.32000, 2.92000, 3.36000, 3.76000, 4.32000, 5.04000, 7.20000])
            keys.append([ 0.57161, 0.73085, 0.90076, 1.49925, 1.92476, 2.06431, 2.02608, 1.80807, 1.51671, 1.30535, 1.22076])

            names.append("LShoulderRoll")
            times.append([ 0.60000, 1.12000, 1.52000, 1.92000, 2.20000, 3.00000, 3.40000, 3.76000, 4.32000, 5.04000, 7.20000])
            keys.append([ 0.34735, 0.66724, 0.65577, 0.63401, 0.05369, 0.49886, 0.53499, 0.57843, 0.63367, 0.58138, 0.27517])

            #names.append("LWristYaw")
            #times.append([ 0.60000, 1.12000, 1.56000])
            #keys.append([ -0.74250, -0.77164, -0.73636])

            names.append("RAnklePitch")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 4.36000, 4.72000, 5.04000, 5.80000, 7.20000])
            keys.append([ 0.78545, 0.76027, 0.76027, 0.66323, 0.78540, 0.66976, 0.78540, 0.78540, 0.54105, 0.48172, -0.36965, -0.78843])

            names.append("RAnkleRoll")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.52000, 3.76000, 4.36000, 4.72000, 5.04000, 5.80000, 7.20000])
            keys.append([ 0.04913, 0.00073, -0.00081, 0.17453, 0.00929, 0.07436, -0.15708, -0.10472, 0.24435, 0.34907, 0.44030, 0.42343, 0.09055])

            names.append("RElbowRoll")
            times.append([ 0.60000, 1.12000, 1.56000, 1.92000, 2.20000, 3.00000, 3.40000, 3.76000, 4.36000, 5.04000, 7.20000])
            keys.append([ 1.21650, 1.04724, 0.66326, 0.73602, 0.00873, 0.07981, 0.05987, 0.03491, 0.35676, 0.49110, 0.97260])

            names.append("RElbowYaw")
            times.append([ 0.60000, 1.12000, 1.48000, 2.20000, 3.00000, 3.40000, 3.76000, 4.36000, 5.04000, 7.20000])
            keys.append([ 0.48010, 1.82235, 2.07443, -0.09919, -0.08134, -0.07674, -0.04813, 0.31000, 1.60817, 0.96638])

            #names.append("RHand")
            #times.append([ 0.60000, 1.12000, 1.56000])
            #keys.append([ 0.00032, 0.00221, 0.00244])

            names.append("RHipPitch")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ -1.55245, -1.57080, -1.57080, -1.57080, -1.52484, -1.57080, -1.55965, -0.84988, -0.67807, -0.64892])

            names.append("RHipRoll")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ -0.14415, -0.13336, -0.21006, -0.54105, -0.55842, -0.73468, -0.61087, -0.25460, -0.08126, -0.07512])

            names.append("RKneePitch")
            times.append([ 0.60000, 1.12000, 1.56000, 2.20000, 3.00000, 3.28000, 3.76000, 5.04000, 5.80000, 7.20000])
            keys.append([ 0.84374, 0.95426, 1.21504, 1.67552, 1.22173, 1.27333, 1.09956, 0.59523, 1.44047, 1.58006])

            names.append("RShoulderPitch")
            times.append([ 0.60000, 0.84000, 1.12000, 1.56000, 2.20000, 3.00000, 3.44000, 3.76000, 4.36000, 5.04000, 7.20000])
            keys.append([ 0.56609, 0.73304, 1.32695, 1.96664, 2.08560, 2.08567, 2.06773, 2.02203, 1.62573, 1.34016, 1.21650])

            names.append("RShoulderRoll")
            times.append([ 0.60000, 1.12000, 1.56000, 1.92000, 2.20000, 3.00000, 3.40000, 3.76000, 4.36000, 5.04000, 7.20000])
            keys.append([ -0.35133, -0.65712, -0.62031, -0.60448, 0.00915, -0.47953, -0.54786, -0.55264, -0.65984, -0.55299, -0.26236])

            #names.append("RWristYaw")
            #times.append([ 0.60000, 1.12000, 1.56000])
            #keys.append([ 1.07529, 1.09523, 1.08756])

            try:
              # uncomment the following line and modify the IP if you use this script outside Choregraphe.
              #motion = ALProxy("ALMotion", IP, 9559)
              #motion = ALProxy("ALMotion")
              self.motion.angleInterpolation(names, keys, times, True);
            except BaseException, err:
              print err

            self.posture.goToPosture("Stand", .6)
        else:
            self.posture.goToPosture("Stand", .6)
        pass
		
    def kickRightLeg(self):
    # Choregraphe simplified export in Python.
        names = list()
        times = list()
        keys = list()

        names.append("HeadPitch")
        times.append([ 1.16000, 2.68000, 3.20000, 4.24000, 5.12000, 6.12000])
        keys.append([ 0.04363, 0.26180, 0.17453, -0.27925, -0.26180, -0.24241])

        names.append("HeadYaw")
        times.append([ 1.16000, 2.68000, 3.20000, 4.24000, 5.12000, 6.12000])
        keys.append([ 0.00464, -0.00149, 0.00311, -0.04905, -0.03371, -0.02459])

        names.append("LAnklePitch")
        times.append([ 1.04000, 1.76000, 2.56000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.03226, 0.01745, 0.01745, 0.03491, 0.03491, 0.11501])

        names.append("LAnkleRoll")
        times.append([ 1.04000, 1.76000, 2.56000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.33161, 0.36652, 0.36652, 0.36652, 0.34732, -0.08433])

        names.append("LElbowRoll")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ -0.74096, -1.03396, -1.36990, -1.02015, -0.70722, -0.37732])

        names.append("LElbowYaw")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ -1.15353, -0.95411, -0.90809, -1.23023, -1.55697, -1.14441])

        #names.append("LHand")
        #times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        #keys.append([ 0.00317, 0.00328, 0.00329, 0.00317, 0.00325, 0.00187])

        names.append("LHipPitch")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.23159, 0.10580, 0.12217, 0.08433, 0.09046, 0.19171, 0.21020])

        names.append("LHipRoll")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.34366, -0.36820, -0.36820, -0.36513, -0.36667, -0.36513, 0.10129])

        names.append("LHipYawPitch")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.18097, -0.25307, -0.06285, -0.05058, -0.18711, -0.24386, -0.31903])

        names.append("LKneePitch")
        times.append([ 1.04000, 1.76000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.08727, -0.08727, -0.09235, -0.07973, -0.07973, -0.07819, -0.07666, -0.09208])

        names.append("LShoulderPitch")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ 1.48649, 1.35917, 1.41746, 1.59847, 1.63835, 1.50021])

        names.append("LShoulderRoll")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ 0.02305, 0.01998, 0.13197, 0.11816, 0.02305, 0.03524])

        #names.append("LWristYaw")
        #times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        #keys.append([ 0.24435, 0.23935, 0.22094, 0.20253, 0.19026, -0.12736])

        names.append("RAnklePitch")
        times.append([ 1.04000, 1.32000, 1.76000, 2.24000, 2.56000, 2.84000, 3.08000, 3.36000, 3.68000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.08727, -0.08727, -0.59341, -0.40143, 0.12217, -0.05236, -0.12217, 0.24435, -0.12217, -0.64403, -0.21991, 0.11356])

        names.append("RAnkleRoll")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.40143, 0.10887, 0.13802, 0.00000, 0.18097, 0.34558, 0.05066])

        names.append("RElbowRoll")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ 0.64117, 1.15353, 1.38056, 1.36062, 0.96024, 0.45564])

        names.append("RElbowYaw")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ 0.99714, 0.86368, 0.90970, 0.63205, 0.84834, 1.49714])

        #names.append("RHand")
        ##times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        #keys.append([ 0.00129, 0.00136, 0.00132, 0.00128, 0.00133, 0.00391])

        names.append("RHipPitch")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.16265, -0.39726, -1.11876, -1.11978, -0.78540, -0.29142, 0.21318])

        names.append("RHipRoll")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.47124, -0.54001, -0.32218, -0.12276, -0.36360, -0.41713, -0.05825])

        names.append("RKneePitch")
        times.append([ 1.04000, 2.56000, 2.84000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.08901, 1.97575, 1.97222, 1.23918, 0.24435, 1.53589, 0.62430, -0.07666])

        names.append("RShoulderPitch")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ 1.52782, 1.46033, 1.47413, 1.24096, 1.51862, 1.54938])

        names.append("RShoulderRoll")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ -0.12268, -0.04138, -0.14569, -0.13955, -0.14722, -0.03993])

       # names.append("RWristYaw")
       # times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        #keys.append([ -0.08727, -0.07359, -0.05058, -0.06285, 0.05680, 0.00149])

        try:
          # uncomment the following line and modify the IP if you use this script outside Choregraphe.
          # motion = ALProxy("ALMotion", IP, 9559)
          #motion = ALProxy("ALMotion")
          self.motion.angleInterpolation(names, keys, times, True);
        except BaseException, err:
          print err
        pass            


    def kickLeftLeg(self):
        print "kicking"
        # Choregraphe simplified export in Python.
        names = list()
        times = list()
        keys = list()

        names.append("HeadPitch")
        times.append([ 1.16000, 2.68000, 3.20000, 4.24000, 5.12000, 6.12000])
        keys.append([ 0.04363, 0.26180, 0.17453, -0.27925, -0.26180, -0.24241])

        names.append("HeadYaw")
        times.append([ 1.16000, 2.68000, 3.20000, 4.24000, 5.12000, 6.12000])
        keys.append([ -0.00464, 0.00149, -0.00311, 0.04905, 0.03371, 0.02459])

        names.append("LAnklePitch")
        times.append([ 1.04000, 1.32000, 1.76000, 2.24000, 2.56000, 2.84000, 3.08000, 3.36000, 3.68000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.08727, -0.08727, -0.59341, -0.40143, 0.12217, -0.05236, -0.12217, 0.24435, -0.12217, -0.64403, -0.21991, 0.11356])

        names.append("LAnkleRoll")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.40143, -0.10887, -0.13802, 0.00000, -0.18097, -0.34558, -0.05066])

        names.append("LElbowRoll")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ -0.64117, -1.15353, -1.38056, -1.36062, -0.96024, -0.45564])

        names.append("LElbowYaw")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ -0.99714, -0.86368, -0.90970, -0.63205, -0.84834, -1.49714])

       # names.append("LHand")
       # times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        #keys.append([ 0.00129, 0.00136, 0.00132, 0.00128, 0.00133, 0.00391])

        names.append("LHipPitch")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.16265, -0.39726, -1.11876, -1.11978, -0.78540, -0.29142, 0.21318])

        names.append("LHipRoll")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.47124, 0.54001, 0.32218, 0.12276, 0.36360, 0.41713, 0.05825])

        names.append("LKneePitch")
        times.append([ 1.04000, 2.56000, 2.84000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.08901, 1.97575, 1.97222, 1.23918, 0.24435, 1.53589, 0.62430, -0.07666])

        names.append("LShoulderPitch")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ 1.52782, 1.46033, 1.47413, 1.24096, 1.51862, 1.54938])

        names.append("LShoulderRoll")
        times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
        keys.append([ 0.12268, 0.04138, 0.14569, 0.13955, 0.14722, 0.03993])

       # names.append("LWristYaw")
       # times.append([ 1.00000, 2.52000, 3.04000, 4.08000, 4.96000, 5.96000])
       # keys.append([ 0.08727, 0.07359, 0.05058, 0.06285, -0.05680, -0.00149])

        names.append("RAnklePitch")
        times.append([ 1.04000, 1.76000, 2.56000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.03226, 0.01745, 0.01745, 0.03491, 0.03491, 0.11501])

        names.append("RAnkleRoll")
        times.append([ 1.04000, 1.76000, 2.56000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.33161, -0.36652, -0.36652, -0.36652, -0.34732, 0.08433])

        names.append("RElbowRoll")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ 0.74096, 1.03396, 1.36990, 1.02015, 0.70722, 0.37732])

        names.append("RElbowYaw")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ 1.15353, 0.95411, 0.90809, 1.23023, 1.55697, 1.14441])

       # names.append("RHand")
       # times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        #keys.append([ 0.00317, 0.00328, 0.00329, 0.00317, 0.00325, 0.00187])

        names.append("RHipPitch")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.23159, 0.10580, 0.12217, 0.08433, 0.09046, 0.19171, 0.21020])

        names.append("RHipRoll")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ 0.34366, 0.36820, 0.36820, 0.36513, 0.36667, 0.36513, -0.10129])

        names.append("RHipYawPitch")
        times.append([ 1.04000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.18097, -0.25307, -0.06285, -0.05058, -0.18711, -0.24386, -0.31903])

        names.append("RKneePitch")
        times.append([ 1.04000, 1.76000, 2.56000, 3.08000, 3.36000, 4.12000, 5.00000, 6.00000])
        keys.append([ -0.08727, -0.08727, -0.09235, -0.07973, -0.07973, -0.07819, -0.07666, -0.09208])

        names.append("RShoulderPitch")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ 1.48649, 1.35917, 1.41746, 1.59847, 1.63835, 1.50021])

        names.append("RShoulderRoll")
        times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        keys.append([ -0.02305, -0.01998, -0.13197, -0.11816, -0.02305, -0.03524])

       # names.append("RWristYaw")
       # times.append([ 1.08000, 2.60000, 3.12000, 4.16000, 5.04000, 6.04000])
        #keys.append([ -0.24435, -0.23935, -0.22094, -0.20253, -0.19026, 0.12736])

        try:
          # uncomment the following line and modify the IP if you use this script outside Choregraphe.
          # motion = ALProxy("ALMotion", IP, 9559)
          #motion = ALProxy("ALMotion")
          self.motion.angleInterpolation(names, keys, times, True);
        except BaseException, err:
          print err
        pass

top = tk.Tk()
button = Nao(top)
top.mainloop()
