#ifndef SPIN_H
#define SPIN_H
#include <string>

enum spin { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };

inline std::string to_string(spin s, bool pretty = true) {
	if (pretty)
		switch (s) {
		case 0: return "Orange to Left";
		case 1: return "Orange to Right";
		case 2: return "Red to Left";
		case 3: return "Red to Right";
		case 4: return "White to Left";
		case 5: return "White to Right";
		case 6: return "Yellow to Left";
		case 7: return "Yellow to Right";
		case 8: return "Blue to Left";
		case 9: return "Blue to Right";
		case 10: return "Green to Left";
		case 11: return "Green to Right";
		}
	else
		switch (s) {
		case 0: return "OL";
		case 1: return "OR";
		case 2: return "RL";
		case 3: return "RR";
		case 4: return "WL";
		case 5: return "WR";
		case 6: return "YL";
		case 7: return "YR";
		case 8: return "BL";
		case 9: return "BR";
		case 10: return "GL";
		case 11: return "GR";
		}
}

inline spin& operator++(spin& s) {
	switch (s % 2) {
	case 0: s = static_cast<spin>(s + 1); return s;
	case 1: s = static_cast<spin>(s - 1); return s;
	}
}
#endif