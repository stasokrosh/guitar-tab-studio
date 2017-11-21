#include "Midi.h"

UCHAR GetFrequency(UCHAR octave, Notes note) {
	return octave * OCTAVE_SIZE + note;
}
