#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H
#include <vector>

namespace DroneTool
{
    class Distribution
    {
    public:

        Distribution(double from, double to, std::vector<double> ys);
        double sample(double x) const;  // Linearly interpolate from corresponding ys

    private:
        double m_from;
        double m_to;
        std::vector<double> m_ys;
    };
}

#endif
