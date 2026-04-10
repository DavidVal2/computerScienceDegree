import subprocess
import sys
import os

def check(solution_file, in_file, out_file):
    # Correr la solución con el input
    with open(in_file, 'r') as f:
        input_data = f.read()
    
    result = subprocess.run(
        ['python3', solution_file],
        input=input_data,
        capture_output=True,
        text=True,
        timeout=10
    )
    
    my_output = result.stdout.strip()
    
    with open(out_file, 'r') as f:
        expected = f.read().strip()
    
    if my_output == expected:
        print(f"✅ CORRECTO - {in_file}")
    else:
        print(f"❌ INCORRECTO - {in_file}")
        print(f"  Esperado:\n{expected}")
        print(f"  Tu output:\n{my_output}")

# Uso: python3 checker.py solution.py test1.in test1.out
if __name__ == '__main__':
    solution = sys.argv[1]
    in_file  = sys.argv[2]
    out_file = sys.argv[3]
    check(solution, in_file, out_file)