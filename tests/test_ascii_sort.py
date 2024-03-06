from subprocess import run, PIPE
import os
import pytest

B_PATH_FILE = './bin/ascii_sort'

def test_bin_folder_contains_ascii_sort():
    assert os.path.isfile(B_PATH_FILE)

def test_ascii_sort_directory_doesnt_exists():
    result = run([B_PATH_FILE], input="123", encoding='utf-8', stderr=PIPE, stdout=PIPE)
    assert result.returncode != 0
    assert "Puck you, Verter!" in result.stderr

def test_ascii_sort():
    dir = "tests/ascii_sort/"
    result = run([B_PATH_FILE], input=f"{dir}", encoding='utf-8', stdout=PIPE)
    assert result.returncode == 0
    assert result.stdout == ""    
    dir_data = run(['ls', f"{dir}"], encoding='utf-8', stdout=PIPE)
    assert dir_data.stdout == "1_file2.txt\n2_file4.txt\n3_file3.txt\n4_file1.txt\n"

if __name__ == "__main__":
    pytest.main()