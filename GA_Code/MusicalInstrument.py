class Instrument:
    
    def __init__(self, max_hold, min_tone, max_tone):
        """
        Inputs: max_hold (max hold time for instrument)
                min_tone (the lowest note the instrument can play)
                max_tone (the highest note the instrument can play)
        Outputs: None

        >>> inst1 = Instrument(1,2,3)
        >>> inst1.max_hold_time
        1
        >>> inst1.min_tone
        2
        >>> inst1.max_tone
        3
        >>> inst2 = Instrument(max_hold=1, max_tone=1, min_tone=1)
        >>> inst2.max_hold_time
        1
        """
        self.max_hold_time = max_hold
        self.min_tone = min_tone
        self.max_tone = max_tone 

def translate_note(inst, note, bias=None):
    """
    Inputs: inst (an Instrument like object)
            note (an arbitrary positive integer, 
                  that's in one octave)
    Outputs: the same note, but in a different octave

    >>> inst1 = Instrument(1, 1, 13)
    >>> inst2 = Instrument(1, 14, 36)
    >>> inst3 = Instrument(1, 37, 49)
    >>> note1 = 12
    >>> note2 = 34
    >>> translate_note(inst1, note1) == note1
    True
    >>> translate_note(inst2, note1) == note1 + 12
    True
    >>> translate_note(inst3, note1) == note1 + 24
    True 
    >>> translate_note(inst3, note2) == note2
    True
    >>> translate_note(inst2, note2) == note2 - 12
    True
    >>> translate_note(inst1, note2) == note2 - 24
    True
    """
    while True:
        if note > inst.max_tone:
            note -= 12
        elif note < inst.min_tone:
            note += 12
        else:
            return note
