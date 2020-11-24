
import datetime


class LogFile:
	
	LOG_FOLDER = '/home/pi/logs/'
	
	def __init__(self):
		self.file_name = datetime.datetime.now().strftime('log_%b_%d_%Y_at_%H_%M_%S.txt')
		self.file_path = LogFile.LOG_FOLDER + self.file_name
		self.file_obj = open(self.file_path, 'w+')
		
	def __write(self, caller_name, message):
		timestamp = datetime.datetime.now().strftime('%m/%d/%Y at %H:%M:%S')
		log_message = '[' + caller_name + ' on ' + timestamp + '] ' + message
		print(log_message)
		self.file_obj.write(log_message + '\n')
		self.file_obj.flush()
		
	def message(self, caller_name, message):
		self.__write(caller_name, 'Message: ' + message)
		
	def warning(self, caller_name, message):
		self.__write(caller_name, 'Warning: ' + message)
		
	def error(self, caller_name, message):
		self.__write(caller_name, 'Error: ' + message)


log_file = LogFile()
