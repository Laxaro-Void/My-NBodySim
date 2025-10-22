#include "config.hpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include "stb_image.h"

template<class A, class B> std::ostream& operator <<(std::ostream& out, const std::pair<A, B> &p) {
	return out << "(" << p.x << ", " << p.y << ")";
}

std::ostream& operator <<(std::ostream& out, const glm::vec3 &v) {
    return out << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

std::ostream& operator <<(std::ostream& out, const glm::mat4 &v) {
    out << "[";
    for (int i = 0; i < 4; i++)
    {
        if (i) out << " ";
        out << "[";
        for (int j = 0; j < 4; j++)
        {
            if (j) out << ", ";
            out << v[i][j];
        }
        out << "]\n";
    }
    return out << "]";
}

template<class A> std::ostream& operator <<(std::ostream& out, const std::vector<A> &v) {
	out << "[";
	for (size_t i = 0; i < v.size(); ++i) {
		if (i) out << ", ";
		out << v[i];
	}
	return out << "]";
}

bool DEBUG = true;