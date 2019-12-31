from termcolor import colored

class StatusHandling():
    def __init__(self):
        self.post_prefix = "------------------------------------%s------------------------------------"

    def error(self, error_text):
        print(colored(error_text, 'red'))

    def success(self, success_text):
        print(colored(success_text, 'green'))

    def warning(self, warning_text):
        print(colored(warning_text, 'yellow'))