Vector = require('vector')

-----------------------------------------------------------------
--                                                             --
--By: Anton Gustavsson(a10antgu) and Jesper Mathiason(a13jesma)--
--                                                             --
-----------------------------------------------------------------

-- all units are in SI units(meters etc)
local InverseMetersPerPixel = 1/5 --5 on screen pixels per meter

local PhysicsAcc = 0
local Physics_TIME_STEP = 1/60
local Physics_G = Vector(0, -9.82)--m/s^2
local Physics_DAMPENING = 0.0
local Physics_ELASTICITY = 0.4
local Physics_FRICTION = 0.15

local LaunchVelocity = Vector(10, 0)
local LaunchPosition = Vector(0, 600 / InverseMetersPerPixel)

local Ball = {}
Ball.Position = Vector(0, 0)
Ball.Velocity = Vector(0, 0)
Ball.Radius = 8 / InverseMetersPerPixel

local PlaneNormal = Vector(0, 1)
PlaneNormal:normalize_inplace()
local PlaneOrigin = Vector(0, 100 / InverseMetersPerPixel)

function LaunchBall(pos, vel)
    Ball.Position = pos or LaunchPosition
    Ball.Velocity = vel or LaunchVelocity
end

function love.load()
    LaunchBall()
end

function love.update(dt)
    PhysicsAcc = PhysicsAcc + dt

    --update the physics each time step, if the dt is larger than Physics_TIME_STEP update more than once if necessary
    while PhysicsAcc >= Physics_TIME_STEP do
    	PhysicsAcc = PhysicsAcc -  Physics_TIME_STEP


        --Add g vector to balls velocity
        Ball.Velocity = (Ball.Velocity + Physics_G) * (1-Physics_DAMPENING)

        --update the balls position
        Ball.Position = Ball.Position + Ball.Velocity

        --Get the distance to the ground plane
        local distanceToPlane = Ball.Radius - ((Ball.Position - PlaneOrigin)*PlaneNormal)

        if distanceToPlane > 0 then

            -- If under ground, move up
            Ball.Position = Ball.Position + (PlaneNormal * distanceToPlane)

            local PlaneNormalDotVel = PlaneNormal*Ball.Velocity

            --get the velocity along the plane in order to apply friction
            local VelocityAlongPlane = ((Ball.Velocity - PlaneNormal*(PlaneNormalDotVel)) * (1-Physics_FRICTION))

            --the velocity along the normal used to calculate the bounce
            local VelocityAlongPlaneNormal = -Physics_ELASTICITY*PlaneNormal*(PlaneNormalDotVel)

            --add the two vectors
            Ball.Velocity = VelocityAlongPlane + VelocityAlongPlaneNormal

        end
    end
end

--no physics here, promise!
function love.draw()
    love.graphics.setBackgroundColor(5, 0, 0)
    love.graphics.setColor(200, 200, 255)
    love.graphics.print("By: Anton Gustavsson and Jesper Mathiason ©", 10, 10)
    love.graphics.print("1, 2, 3 : different startPositions and startVelocities", 10, 30)
    love.graphics.print("q, w, e : different plane slopes", 10, 50)
    love.graphics.print("a, s, d : different ELASTICITY : " .. Physics_ELASTICITY, 10, 70)
    love.graphics.print("z, x, c : different FRICTION : " .. Physics_FRICTION, 10, 90)

    love.graphics.translate(200, 600)
    love.graphics.scale(InverseMetersPerPixel, -InverseMetersPerPixel )

    local LineVector =  (PlaneNormal:perpendicular() * 10000)

    love.graphics.line(PlaneOrigin.x + LineVector.x, PlaneOrigin.y + LineVector.y, PlaneOrigin.x - LineVector.x, PlaneOrigin.y - LineVector.y)

    love.graphics.circle("fill", Ball.Position.x, Ball.Position.y, Ball.Radius, 32)
end

--handle key inputs, to setup diffrent scenarios
function love.keypressed(key, isrepeat)
    if key == "escape" then
        love.event.quit()
    end

    if key == "1" then
        LaunchBall()--Default
    end

    if key == "2" then
        LaunchBall(Vector(0, 300 / InverseMetersPerPixel), Vector(150, 0))
    end

    if key == "3" then
        LaunchBall(Vector(0, 100 / InverseMetersPerPixel), Vector(50, 200))
    end

    if key == "q" then--Default
        PlaneNormal = Vector(0, 1)
        PlaneNormal:normalize_inplace()
    end

    if key == "w" then
        PlaneNormal = Vector(-0.2, 1)
        PlaneNormal:normalize_inplace()
    end

     if key == "e" then
        PlaneNormal = Vector(0.1, 1)
        PlaneNormal:normalize_inplace()
    end

    if key == "a" then--Default
        Physics_ELASTICITY = 0.4
    end

    if key == "s" then
        Physics_ELASTICITY = 1.0
    end

     if key == "d" then
        Physics_ELASTICITY = 0.0
    end

    if key == "z" then--Default
        Physics_FRICTION = 0.15
    end

    if key == "x" then
        Physics_FRICTION = 0.8
    end

    if key == "c" then
        Physics_FRICTION = 0.0
    end

    if key == "r" then
        LaunchBall()

    end
end