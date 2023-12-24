#!/usr/bin/env python3

import z3
import sys
import re

lines = list(map(
    lambda l: list(map(int, l.strip().replace('@', ',').split(','))),
    sys.stdin.readlines()))
print(lines)

def I(name):
    return z3.Int(name)

x, y, z = I('x'), I('y'), I('z')
vx, vy, vz = I('vx'), I('vy'), I('vz')

solver = z3.Solver()
for i in range(len(lines)):
    [a, b, c, va, vb, vc] = lines[i]
    ti = I(f"t{i}")
    solver.add(ti >= 0)
    solver.add(x + ti * vx == a + ti * va)
    solver.add(y + ti * vy == b + ti * vb)
    solver.add(z + ti * vz == c + ti * vc)

print(solver.check())
print(solver.model()[x],
      solver.model()[y],
      solver.model()[z],
      solver.model()[vx],
      solver.model()[vy],
      solver.model()[vz])

print(solver.model()[x].as_long() +
      solver.model()[y].as_long() +
      solver.model()[z].as_long())
