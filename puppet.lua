--
-- CS488 -- Introduction to Computer Graphics
-- 
-- a3mark.lua
--
-- A very simple scene creating a trivial puppet.  The TAs will be
-- using this scene as part of marking your assignment.  You'll
-- probably want to make sure you get reasonable results with it!


red = gr.material({1.0, 0.0, 0.0}, {0.1, 0.1, 0.1}, 1)
blue = gr.material({0.0, 0.0, 1.0}, {0.1, 0.1, 0.1}, 1)
green = gr.material({0.0, 1.0, 0.0}, {0.1, 0.1, 0.1}, 1)
white = gr.material({1.0, 1.0, 1.0}, {0.1, 0.1, 0.1}, 10)
black = gr.material({0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, 0)

rootnode = gr.node('root')

--Torso Representation
torso = gr.sphere('torso')
rootnode:add_child(torso)
torso:set_material(green)
torso:scale(1.0, 1.5, 0.5)

--Shoulder Base
shoulderBase = gr.node('shoulderBase')
rootnode:add_child(shoulderBase)
shoulderBase:translate(0.0, 1.5, 0.0)

--Shoulder Representation
shoulder = gr.sphere('shoulder')
shoulderBase:add_child(shoulder)
shoulder:set_material(green)
shoulder:scale(1.4, 0.3, 0.5)

--Hip Base
hipBase = gr.node('hipBase')
rootnode:add_child(hipBase)
hipBase:translate(0.0, -1.5, 0.0)

--Hip
hip = gr.sphere('hip')
hipBase:add_child(hip)
hip:set_material(blue)
hip:scale(0.9, 0.5, 0.7)

--Neck

neckBase = gr.node('neckBase')
shoulderBase:add_child(neckBase)

neckJoint = gr.joint('neckJoint', {-15.0, 0.0, 15.0}, {0.0, 0.0, 0.0})
neckBase:add_child(neckJoint)

neck = gr.sphere('neck')
neckJoint:add_child(neck)
neck:set_material(green)
neck:translate(0, 0.5, 0)
neck:scale(0.3, 0.5, 0.3)

--Head

headBase = gr.node('headBase')
neckJoint:add_child(headBase)
headBase:translate(0.0, 0.5, 0.0)

headJoint = gr.joint('headJoint', {-45.0, 0.0, 45.0}, {-45.0, 0.0, 45.0})
headBase:add_child(headJoint)

head = gr.sphere('head')
headJoint:add_child(head)
head:set_material(green)
head:translate(0, 1.0, 0)
head:scale(1.0, 1.0, 1.0)

nose = gr.sphere('nose')
headJoint:add_child(nose)
nose:set_material(white)
nose:translate(0.0, 0.8, 0.6)
nose:scale(0.1, 0.4, 0.5)

--Upper Arm

upperArmBaseL = gr.node('upperArmBaseL')
shoulderBase:add_child(upperArmBaseL)
upperArmBaseL:translate(-1.4, 0.0, 0.0)
upperArmBaseL:rotate('y', 90.0)

upperArmJointL = gr.joint('upperArmJointL', {-90.0, 0.0, 0.0}, {0.0, 0.0, 0.0})
upperArmBaseL:add_child(upperArmJointL)

upperArmL = gr.sphere('upperArmL')
upperArmJointL:add_child(upperArmL)
upperArmL:set_material(white)
upperArmL:translate(0.0, -1.0, 0.0)
upperArmL:scale(0.3, 1.0, 0.3)

upperArmBaseR = gr.node('upperArmBaseR')
shoulderBase:add_child(upperArmBaseR)
upperArmBaseR:translate(1.4, 0.0, 0.0)
upperArmBaseR:rotate('y', -90.0)

upperArmJointR = gr.joint('upperArmJointR', {0.0, 90.0, 90.0}, {0.0, 0.0, 0.0})
upperArmBaseR:add_child(upperArmJointR)

upperArmR = gr.sphere('upperArmR')
upperArmJointR:add_child(upperArmR)
upperArmR:set_material(white)
upperArmR:translate(0.0, -1.0, 0.0)
upperArmR:scale(0.3, 1.0, 0.3)

--Forearm
forearmBaseL = gr.node('forearmBaseL')
upperArmJointL:add_child(forearmBaseL)
forearmBaseL:translate(0.0, -1.9, 0.0)

forearmJointL = gr.joint('forearmJointL', {-90.0, -90.0, 0.0}, {0.0, 0.0, 0.0})
forearmBaseL:add_child(forearmJointL)

forearmL = gr.sphere('forearmL')
forearmJointL:add_child(forearmL)
forearmL:set_material(white)
forearmL:translate(0.0, -0.75, 0.0)
forearmL:scale(0.3, 0.75, 0.3)

forearmBaseR = gr.node('forearmBaseR')
upperArmJointR:add_child(forearmBaseR)
forearmBaseR:translate(0.0, -1.9, 0.0)

forearmJointR = gr.joint('forearmJointR', {0.0, 90.0, 90.0}, {0.0, 0.0, 0.0})
forearmBaseR:add_child(forearmJointR)

forearmR = gr.sphere('forearmR')
forearmJointR:add_child(forearmR)
forearmR:set_material(white)
forearmR:translate(0.0, -0.75, 0.0)
forearmR:scale(0.3, 0.75, 0.3)

--Hand
handBaseL = gr.node('handBaseL')
forearmJointL:add_child(handBaseL)
handBaseL:translate(0.0, -1.5, 0.0)

handJointL = gr.joint('handJointL', {-90.0, 90.0, 90.0}, {0.0, 0.0, 0.0})
handBaseL:add_child(handJointL)

handL = gr.sphere('handL')
handJointL:add_child(handL)
handL:set_material(green)
handL:translate(0.0, -0.3, 0.0)
handL:scale(0.3, 0.4, 0.3)

handBaseR = gr.node('handBaseR')
forearmJointR:add_child(handBaseR)
handBaseR:translate(0.0, -1.5, 0.0)

handJointR = gr.joint('handJointR', {-90.0, -90.0, 90.0}, {0.0, 0.0, 0.0})
handBaseR:add_child(handJointR)

handR = gr.sphere('handR')
handJointR:add_child(handR)
handR:set_material(green)
handR:translate(0.0, -0.3, 0.0)
handR:scale(0.3, 0.4, 0.3)

--Thigh
thighBaseL = gr.node('thighBaseL')
hipBase:add_child(thighBaseL)
thighBaseL:translate(-0.6, 0.1, 0.0)
thighBaseL:rotate('y', -90.0)

thighJointL = gr.joint('thighJointL', {0.0, 90.0, 90.0}, {0.0, 0.0, 0.0})
thighBaseL:add_child(thighJointL)

thighL = gr.sphere('thighL')
thighJointL:add_child(thighL)
thighL:set_material(blue)
thighL:translate(0.0, -1.25, 0.0)
thighL:scale(0.5, 1.25, 0.5)

thighBaseR = gr.node('thighBaseR')
hipBase:add_child(thighBaseR)
thighBaseR:translate(0.6, 0.1, 0.0)
thighBaseR:rotate('y', -90.0)


thighJointR = gr.joint('thighJointR', {0.0, 0.0, 90.0}, {0.0, 0.0, 0.0})
thighBaseR:add_child(thighJointR)

thighR = gr.nh_box('thighR', {20, 50, -10}, 15)
thighJointR:add_child(thighR)
thighR:set_material(blue)
thighR:translate(0.0, -1.25, 0.0)
thighR:scale(0.5, 1.25, 0.5)

--Calf
calfBaseL = gr.node('calfBaseL')
thighJointL:add_child(calfBaseL)
calfBaseL:translate(0.0, -2.4, 0.0)
calfBaseL:rotate('y', 180.0)

calfJointL = gr.joint('calfJointL', {0.0, 45.0, 135.0}, {0.0, 0.0, 0.0})
calfBaseL:add_child(calfJointL)

calfL = gr.sphere('calfL')
calfJointL:add_child(calfL)
calfL:set_material(blue)
calfL:translate(0.0, -1.25, 0.0)
calfL:scale(0.3, 1.25, 0.3)

calfBaseR = gr.node('calfBaseR')
thighJointR:add_child(calfBaseR)
calfBaseR:translate(0.0, -2.4, 0.0)
calfBaseR:rotate('y', 180.0)

calfJointR = gr.joint('calfJointR', {0.0, 45.0, 135.0}, {0.0, 0.0, 0.0})
calfBaseR:add_child(calfJointR)

calfR = gr.sphere('calfR')
calfJointR:add_child(calfR)
calfR:set_material(blue)
calfR:translate(0.0, -1.25, 0.0)
calfR:scale(0.3, 1.25, 0.3)

--Foot
footBaseL = gr.node('footBaseL')
calfJointL:add_child(footBaseL)
footBaseL:translate(0.0, -2.4, 0.0)
footBaseL:rotate('z', -90.0)

footJointL = gr.joint('footJointL', {-10.0, 0.0, 10}, {0.0, 0.0, 0.0})
footBaseL:add_child(footJointL)

footL = gr.sphere('footL')
footJointL:add_child(footL)
footL:set_material(blue)
footL:translate(0.0, -0.2, 0.0)
footL:scale(0.3, 0.4, 0.3)

footBaseR = gr.node('footBaseR')
calfJointR:add_child(footBaseR)
footBaseR:translate(0.0, -2.4, 0.0)
footBaseR:rotate('z', -90.0)

footJointR = gr.joint('footJointR', {0.0, 0.0, 50.0}, {0.0, 0.0, 0.0})
footBaseR:add_child(footJointR)

footR = gr.sphere('footR')
footJointR:add_child(footR)
footR:set_material(blue)
footR:translate(0.0, -0.2, 0.0)
footR:scale(0.3, 0.4, 0.3)

rootnode:translate(0.0, 0.0, -10.0)
rootnode:scale(0.5, 0.5, 0.5)

return rootnode
