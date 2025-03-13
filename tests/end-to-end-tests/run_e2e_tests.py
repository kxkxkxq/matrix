import os
import subprocess

def compare_output(output, expected):
    return output.strip() == expected.strip()

def main():
    cpp_executable = "./build/src/determinant"
    
    if not os.path.isfile(cpp_executable) or not os.access(cpp_executable, os.X_OK):
        print(f"File '{cpp_executable}' not found")
        return
    
    current_directory = os.getcwd()
    data_folder = os.path.join(current_directory, "tests", "end-to-end-tests", "data")
    answers_folder = os.path.join(current_directory, "tests", "end-to-end-tests", "answers")
    
    test_files = [f for f in os.listdir(data_folder) if f.startswith("test") and f.endswith(".dat")]
    test_files.sort() 

    passed_tests = 0
    for test_file in test_files:
        test_path = os.path.join(data_folder, test_file)
        test_number = test_file.split('.')[0] 
        
        answer_file = f"{test_number}_answ.dat"
        answer_path = os.path.join(answers_folder, answer_file)
        
        if not os.path.exists(answer_path):
            print(f"Can't find {test_number} answers file")
            continue
        
        with open(test_path, "r") as f:
            test_input = f.read()
        
        try:
            result = subprocess.run(
                [cpp_executable],
                input=test_input,
                text=True,
                capture_output=True,
                check=True
            )
            program_output = result.stdout
        except subprocess.CalledProcessError as e:
            print(f"Error while testing test : {test_number}: {e}")
            continue
        
        with open(answer_path, "r") as f:
            expected_output = f.read()
        
        if compare_output(program_output, expected_output):
            print(f"Test {test_number}: passed")
            passed_tests += 1
        else:
            print(f"Test {test_number}: failed")
            print(f"Expected:\n{expected_output}")
            print(f"Programme output:\n{program_output}")

    total_tests = len(test_files)
    print("\n=== RESULT ===")
    print(f"tests ran: {total_tests}")
    print(f"TESTS PASSED: {passed_tests}")
    if (total_tests - passed_tests) > 0 :
        print(f"TESTS FAILED: {total_tests - passed_tests}")

if __name__ == "__main__":
    main()