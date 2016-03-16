def to_range(value, new_range):
    return value % (max(new_range) - min(new_range)) + min(new_range)
