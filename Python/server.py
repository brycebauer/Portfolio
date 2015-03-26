from naoqi import ALProxy

def __init__(self, top):
        IP = "192.168.1.X"
        #change X to last part of ID in class.
        self.motion = ALProxy("ALMotion", IP, 9559)
        self.posture = ALProxy("ALRobotPosture", IP, 9559)

