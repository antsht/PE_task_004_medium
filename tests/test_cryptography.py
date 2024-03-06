from subprocess import run, PIPE
import os
import pytest

B_PATH_FILE = './bin/cryptography'

def test_bin_folder_contains_cryptography():
    assert os.path.isfile(B_PATH_FILE)

def test_cryptography_file_doesnt_exists():
    result = run([B_PATH_FILE], input="123", encoding='utf-8', stdout=PIPE, stderr=PIPE)
    assert result.returncode != 0
    assert "Puck you, Verter!" in result.stderr

def test_cryptography():
    file = "tests/cryptography/chifre_me.txt"
    result = run([B_PATH_FILE], input=f"{file}", encoding='utf-8', stdout=PIPE)
    assert result.stdout == ""
    file_data = run(['cat', f"{file}"], encoding='utf-8', stdout=PIPE)
    assert file_data.stdout == "x ficmhpt m GRR iFn m fvpLyKi m teQ ndYgy Xky HOC"

if __name__ == "__main__":
    pytest.main()