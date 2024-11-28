#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <vector>

namespace DroneTool
{
    class Distribution
    {
    public:

        Distribution(const double from, const double to, std::vector<double> ys) : m_from(from), m_to(to), m_ys(std::move(ys)) {}
        [[nodiscard]] double sample(double x) const;  // Linearly interpolate from corresponding ys

    private:
        double m_from;
        double m_to;
        std::vector<double> m_ys;
    };
}

#endif
