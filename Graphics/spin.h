#ifndef SPIN_H
#define SPIN_H

enum spin { OL, OR, RL, RR, WL, WR, YL, YR, BL, BR, GL, GR };

inline spin& operator++(spin& s) {
	switch (s % 2) {
	case 0: s = static_cast<spin>(s + 1); return s;
	case 1: s = static_cast<spin>(s - 1); return s;
	}
}
#endif