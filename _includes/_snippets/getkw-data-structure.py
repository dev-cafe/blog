import json


class Section:
    def __init__(self, name, keywords={}, sections={}):
        self.name = name
        self.keywords = keywords
        self.sections = sections

    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, indent=4)

class Keyword:
    def __init__(self, key, value):
        self.key = key
        self.value = value

    def toJSON(self):
        return json.dumps(self, default=lambda o: o.__dict__, indent=4)

    def __str__(self):
        return 'Key {} with value {} and type {}'.format(self.key, self.value, type(self.value))
