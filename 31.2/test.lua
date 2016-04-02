require"lproc"
lproc.start("lproc.send(\"ch\", \"test\", true, 123)")
print(lproc.receive("ch"))
lproc.exit()
