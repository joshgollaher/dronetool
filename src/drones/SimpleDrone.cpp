#include <algorithm>
#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <drones/SimpleDrone.h>
#include <LinearMath/btDefaultMotionState.h>

namespace DroneTool
{
    static std::vector<double> generate_rpm_thrust_curve(const double max_rpm, const int steps) {
        std::vector<double> thrust_values;

        for (int i = 0; i < steps; ++i) {
            constexpr double k = 10.0;
            const double rpm = i * max_rpm / (steps - 1); // Evenly spaced RPM
            double thrust = k * std::log(rpm + 1); // Logarithmic thrust
            thrust_values.push_back(thrust);
        }
        return thrust_values;
    }

    SimpleDrone::SimpleDrone()
    {
        m_battery = new Battery(3150);

        constexpr double max_rotor_rpm = 14000;
//        const Distribution rpm_thrust_curve(0, max_rotor_rpm, generate_rpm_thrust_curve(max_rotor_rpm, 100));
        const Distribution rpm_thrust_curve(0, max_rotor_rpm, {0, 10});
        const Distribution rpm_power_draw_curve(0, max_rotor_rpm, {0, 45}); // Linear curve for now
        m_rotor_1 = new Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve);
        m_rotor_2 = new Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve);
        m_rotor_3 = new Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve);
        m_rotor_4 = new Rotor(max_rotor_rpm, rpm_thrust_curve, rpm_power_draw_curve);

        m_modules.push_back(m_battery);
        m_modules.push_back(m_rotor_1);
        m_modules.push_back(m_rotor_2);
        m_modules.push_back(m_rotor_3);
        m_modules.push_back(m_rotor_4);
    }

    SimpleDrone::~SimpleDrone()
    {
        delete m_battery;
        delete m_rotor_1;
        delete m_rotor_2;
        delete m_rotor_3;
        delete m_rotor_4;
    }

    void SimpleDrone::setup()
    {
    }

    void SimpleDrone::update(float delta_time)
    {
        // Apply force from rotors
        btTransform transform;
        m_bullet_rigid_body->getMotionState()->getWorldTransform(transform);

        const btVector3 local_up(0, 1, 0);
        const btVector3 world_up = transform.getBasis() * local_up;

        m_bullet_rigid_body->applyForce(world_up * m_rotor_1->get_thrust(), transform * m_rotor_1_pos - m_bullet_rigid_body->getCenterOfMassPosition());
        m_bullet_rigid_body->applyForce(world_up * m_rotor_2->get_thrust(), transform * m_rotor_2_pos - m_bullet_rigid_body->getCenterOfMassPosition());
        m_bullet_rigid_body->applyForce(world_up * m_rotor_3->get_thrust(), transform * m_rotor_3_pos - m_bullet_rigid_body->getCenterOfMassPosition());
        m_bullet_rigid_body->applyForce(world_up * m_rotor_4->get_thrust(), transform * m_rotor_4_pos - m_bullet_rigid_body->getCenterOfMassPosition());
    }

    void SimpleDrone::setup_bullet_rigid_body()
    {
        // Spawn at origin
        // 1.25ft = 0.381m
        // 0.75ft = 0.24384m
        const btVector3 half_extents(0.381 / 2, 0.24384 / 2, 0.381 / 2);
        btCollisionShape* box_shape = new btBoxShape(half_extents);

        btVector3 local_inertia(0, 0, 0);
        box_shape->calculateLocalInertia(m_mass_kg, local_inertia);

        auto* motion_state = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, half_extents.y(), 0)));

        const btRigidBody::btRigidBodyConstructionInfo construction_info(m_mass_kg, motion_state, box_shape, local_inertia);
        m_bullet_rigid_body = new btRigidBody(construction_info);

        m_rotor_1_pos = btVector3( 0.381 / 2,  0.24384 / 2,  0.381 / 2); // Top-right-front
        m_rotor_2_pos = btVector3(-0.381 / 2,  0.24384 / 2,  0.381 / 2); // Top-left-front
        m_rotor_3_pos = btVector3( 0.381 / 2,  0.24384 / 2, -0.381 / 2); // Top-right-back
        m_rotor_4_pos = btVector3(-0.381 / 2,  0.24384 / 2, -0.381 / 2); // Top-left-back
    }
}
