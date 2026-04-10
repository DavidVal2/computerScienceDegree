import subprocess
import sys
import os

def check(solution_file, in_file, out_file):
    # Leer input
    with open(in_file, 'r') as f:
        input_data = f.read()

    # Detectar tipo de archivo
    if solution_file.endswith(".py"):
        cmd = ['python3', solution_file]

    elif solution_file.endswith(".cpp"):
        exe = "solution_exe"

        # Compilar C++
        compile_result = subprocess.run(
            ['g++', solution_file, '-o', exe],
            capture_output=True,
            text=True
        )

        if compile_result.returncode != 0:
            print("❌ Error de compilación:")
            print(compile_result.stderr)
            return

        cmd = [exe + '.exe']

    else:
        print("❌ Formato de archivo no soportado.")
        return

    # Ejecutar solución
    result = subprocess.run(
        cmd,
        input=input_data,
        capture_output=True,
        text=True,
        timeout=10
    )

    my_output = result.stdout.strip()

    # Leer output esperado
    with open(out_file, 'r') as f:
        expected = f.read().strip()

    # Comparar
    if my_output == expected:
        print(f"✅ CORRECTO - {in_file}")
    else:
        print(f"❌ INCORRECTO - {in_file}")
        print("------ Esperado ------")
        print(expected)
        print("------ Tu output ------")
        print(my_output)


# Uso: python3 checker.py solution.cpp test1.in test1.out
if __name__ == '__main__':
    solution = sys.argv[1]
    in_file  = sys.argv[2]
    out_file = sys.argv[3]
    check(solution, in_file, out_file)