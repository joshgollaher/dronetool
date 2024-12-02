#include <Simulation.h>
#include <Drone.h>
#include <fstream>

namespace DroneTool
{
    Simulation::Simulation(Drone* drone)
    {
        m_drone = drone;
    }

    Simulation::~Simulation()
    {
        // FIXME: Step through m_bullet_world and delete all attached rigidbodies
        delete m_bullet_collision_config;
        delete m_bullet_broadphase;
        delete m_bullet_collision_dispatcher;
        delete m_bullet_constraint_solver;
        delete m_drone;
    }

    void Simulation::initialize(const double area_width, const double area_depth)
    {
        m_area_width = area_width;
        m_area_depth = area_depth;

        // Create bullet world
        m_bullet_collision_config = new btDefaultCollisionConfiguration;
        m_bullet_collision_dispatcher = new btCollisionDispatcher(m_bullet_collision_config);
        m_bullet_broadphase = new btDbvtBroadphase;
        m_bullet_constraint_solver = new btSequentialImpulseConstraintSolver;
        m_bullet_world = new btDiscreteDynamicsWorld(m_bullet_collision_dispatcher, m_bullet_broadphase,
                                                     m_bullet_constraint_solver, m_bullet_collision_config);
        m_bullet_world->setGravity(btVector3(0, -9.81, 0));

        // Create play-area
        build_environment();

        m_bullet_world->addRigidBody(m_drone->bullet_body());

        m_drone->setup();
    }

    void Simulation::update(const float delta_time)
    {
        m_bullet_world->stepSimulation(delta_time, 10);

        btTransform drone_transform;
        m_drone->bullet_body()->getMotionState()->getWorldTransform(drone_transform);
        const auto pos = drone_transform.getOrigin();

        m_drone->set_position(std::make_tuple(pos.x(), pos.y(), pos.z()));

        m_drone->update(delta_time);
    }

    void Simulation::transmit_data(PacketCommand command, const std::vector<uint8_t>& data)
    {
    }

    std::optional<std::pair<PacketCommand, std::vector<uint8_t>>> Simulation::receive_data()
    {
        // Will use this in the future to mimic data reception. Empty for now...
        return {};
    }

    void Simulation::export_world(const std::string& file_name) const
    {
        btDefaultSerializer* serializer = new btDefaultSerializer;
        m_bullet_world->serialize(serializer);

        std::ofstream os(file_name, std::ios::binary);
        os.write(reinterpret_cast<const char*>(serializer->getBufferPointer()), serializer->getCurrentBufferSize());
        os.close();
        delete serializer;
    }

    void Simulation::build_environment() const
    {
        // TODO: this causes a memory leak, clean these up

        // Ground plane at y = 0
        btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 0); // Plane facing up
        auto groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
        btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, groundMotionState, groundShape,
                                                                   btVector3(0, 0, 0));
        auto groundRigidBody = new btRigidBody(groundRigidBodyCI);
        m_bullet_world->addRigidBody(groundRigidBody);

        // Create the walls (static boxes)
        btCollisionShape* wallShape = new btBoxShape(btVector3(m_area_width / 2, m_area_depth, 0.1f)); // A thin box for walls

        // Front wall (positive z-direction)
        btTransform frontWallTransform;
        frontWallTransform.setIdentity();
        frontWallTransform.setOrigin(btVector3(0, m_area_depth / 2, m_area_depth / 2));
        auto frontWallMotionState = new btDefaultMotionState(frontWallTransform);
        btRigidBody::btRigidBodyConstructionInfo frontWallCI(0, frontWallMotionState, wallShape, btVector3(0, 0, 0));
        auto frontWall = new btRigidBody(frontWallCI);
        m_bullet_world->addRigidBody(frontWall);

        // Back wall (negative z-direction)
        btTransform backWallTransform;
        backWallTransform.setIdentity();
        backWallTransform.setOrigin(btVector3(0, m_area_depth / 2, -m_area_depth / 2));
        auto backWallMotionState = new btDefaultMotionState(backWallTransform);
        btRigidBody::btRigidBodyConstructionInfo backWallCI(0, backWallMotionState, wallShape, btVector3(0, 0, 0));
        auto backWall = new btRigidBody(backWallCI);
        m_bullet_world->addRigidBody(backWall);

        // Left wall (negative x-direction)
        btCollisionShape* sideWallShape = new btBoxShape(btVector3(0.1f, m_area_depth, m_area_width / 2)); // Wall rotated 90 degrees
        btTransform leftWallTransform;
        leftWallTransform.setIdentity();
        leftWallTransform.setOrigin(btVector3(-m_area_width / 2, m_area_depth / 2, 0));
        auto leftWallMotionState = new btDefaultMotionState(leftWallTransform);
        btRigidBody::btRigidBodyConstructionInfo leftWallCI(0, leftWallMotionState, sideWallShape, btVector3(0, 0, 0));
        auto leftWall = new btRigidBody(leftWallCI);
        m_bullet_world->addRigidBody(leftWall);

        // Right wall (positive x-direction)
        btTransform rightWallTransform;
        rightWallTransform.setIdentity();
        rightWallTransform.setOrigin(btVector3(m_area_width / 2, m_area_depth / 2, 0));
        auto rightWallMotionState = new btDefaultMotionState(rightWallTransform);
        btRigidBody::btRigidBodyConstructionInfo
            rightWallCI(0, rightWallMotionState, sideWallShape, btVector3(0, 0, 0));
        auto rightWall = new btRigidBody(rightWallCI);
        m_bullet_world->addRigidBody(rightWall);
    }
}

