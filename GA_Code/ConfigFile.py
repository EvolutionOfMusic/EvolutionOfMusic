def basic_parse(file_name):
    """
    Parses a config file with format:

    <Field Name 0>: <Value 0>
    <Field Name 1>: <Value 1>
    .
    .
    .
    <Field Name n>: <Value n>

    Inputs: config file name
    Outputs: a dictionary consisting of Field Name Value pairs
    """
    with open(file_name) as config_file:
        file_list = config_file.read().replace(': ', '\n').strip('\n').split('\n')
        file_list = [(file_list[2 * i], file_list[2 * i + 1]) for i in range(len(file_list)//2)]
        fields, values = map(list, zip(*file_list))

        fields = [field.replace(" ", "_") for field in fields]
        
        for i in range(len(values)):
            try:
                values[i] = int(values[i])
            except ValueError:
                continue

        return dict(zip(fields, values))

    
class ConfigFile:
    def __init__(self, file_name, parser=basic_parse):
        self.__dict__ = parser(file_name)

