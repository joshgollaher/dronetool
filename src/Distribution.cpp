#include <cassert>
#include <Distribution.h>

namespace DroneTool
{
    double Distribution::sample(const double x) const
    {
        assert(x >= m_from && x <= m_to);

        const double spacing = static_cast<double>(m_to - m_from) / m_ys.size();
        const auto idx = static_cast<size_t>((x - m_from) / spacing);

        if (idx >= m_ys.size() - 1)
        {
            return m_ys.back();
        }

        // How away from idx the x is
        const double local_x = (x - (m_from + idx * spacing)) / spacing;

        return m_ys[idx] + local_x * (m_ys[idx + 1] - m_ys[idx]);
    }
}
