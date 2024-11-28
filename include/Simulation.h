#ifndef SIMULATION_H
#define SIMULATION_H

#include <optional>
#include <btBulletDynamicsCommon.h>

#include <Packet.h>

namespace DroneTool
{
    class Simulation
    {
    public:
        explicit Simulation(class Drone* drone);
        ~Simulation();

        void initialize(double area_width, double area_depth);
        void update(float delta_time);

        void transmit_data(PacketCommand command, const std::vector<uint8_t>& data);
        std::optional<std::pair<PacketCommand, std::vector<uint8_t>>> receive_data();

    private:
        void build_environment() const;

        class Drone* m_drone;

        double m_area_width{0}, m_area_depth{0};

        // Bullet Physics
        btDiscreteDynamicsWorld* m_bullet_world{nullptr};
        btDefaultCollisionConfiguration* m_bullet_collision_config{nullptr};
        btCollisionDispatcher* m_bullet_collision_dispatcher{nullptr};
        btBroadphaseInterface* m_bullet_broadphase{nullptr};
        btSequentialImpulseConstraintSolver* m_bullet_constraint_solver{nullptr};
    };
}

#endif
