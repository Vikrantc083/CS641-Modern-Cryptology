import pexpect
#Loging into the game Server
child = pexpect.spawn('ssh student@172.27.26.188')
child.expect('student@172.27.26.188\'s password:')
child.sendline('cs641')
child.expect('Enter your group name: ', timeout=1) 
#Group name
child.sendline("SecureSavants")

child.expect('Enter password: ', timeout=1)
#Group Password
child.sendline("vikrantc672")

child.expect('\r\n\r\n\r\nYou have solved 3 levels so far.\r\nLevel you want to start at: ', timeout=1)
#Since we have already cleared level 3 kindly change "solved 3 levels" to "solved 4 levels"
child.sendline("4")

#Entering Commands Sequence
child.expect('.*')
child.sendline("go")

child.expect('.*')
child.sendline("dive")

child.expect('.*')
child.sendline("dive")

child.expect('.*')
child.sendline("back")

child.expect('.*')
child.sendline("pull")


child.expect('.*')
child.sendline("go")

child.expect('.*')
child.sendline("back")

child.expect('.*')
child.sendline("enter")

child.expect('.*')
child.sendline("wave")

child.expect('.*')
child.sendline("back")

child.expect('.*')
child.sendline("back")

child.expect('.*')
child.sendline("thrnxxtzy")

child.expect('.*')
child.sendline("read")

child.expect('.*')
child.sendline("the_magic_of_wand")

child.expect('.*')
child.sendline("c")

child.expect('.*')
child.sendline("read")

#Plaintext-Ciphertext Files
file1 = open("plaintext1.txt", 'r')
file2= open("ciphertext1.txt",'w')

for line in file1.readlines():
	child.sendline(line)
	print(child.before)
	file2.writelines(str(child.before)[48:64]+"\n")
	child.expect("Slowly, a new text starts*")
	child.sendline("c")
	child.expect('The text in the screen vanishes!')

data = child.read()
print(data)
child.close()
print(child.before, child.after)

file1.close()
file2.close()
