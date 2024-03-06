#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale>


std::string fileOut(std::string file_)
{
	file_ += ".txt";
    std::ifstream file(file_);

    std::string text_file = "";
    std::string text = "";

    // Проверяем, удалось ли открыть файл
    if (!file.is_open())
    {
        std::cout << "Unable to open the file." << std::endl;
        exit(1); // Если не удалось открыть файл, выходим из функции
    }

    // Читаем содержимое файла построчно
    while (getline(file, text)) // Используем getline для чтения строк из файла
    {
    	text_file += text;
    }

    file.close();

    return text_file;//сдесь хранится весь текст из файла в строке
}

std::vector<std::string> text_split(std::string text_file)
{
	std::vector<std::string> text;
	std::string text_file_copy;
	for (int i = 0, index = 1; i < size(text_file); ++i)
	{
		if (text_file[i] != '.' && text_file[i] != '!' && text_file[i] != '?')
		{
			text_file_copy += text_file[i];
		}else
		{
			text_file_copy = text_file_copy;//тут магия, мы собираем из костылей нормальную строку, перед загрузкой в вектор
			text.push_back(text_file_copy);
			text_file_copy = "";
			index++;//это индекс для предложений, чтобы понимать какие они по счету, добавляется при образовании нового элемента в векторе
		}
	}

	return text;//это вектор, в котором каждый элемент - это каждая по очереди строка из файла без . ? !
}

std::vector<std::string> last_word(std::vector<std::string> text_algoritm)//алгоритм поиска последнего слова
{
	std::string copu_dopoln;
	std::string copy_text;
	std::vector<std::string> dopoln;

	for (int i = 0; i < text_algoritm.size(); ++i)//пробегаемся по вектору предложений
	{
		int j;
		copy_text = text_algoritm[i];
		for (j = 0; copy_text[j + 1] != '\0'; ++j)
		{

		}

		for (; copy_text[j] != ' '; --j)
		{
			copu_dopoln = copy_text[j] + copu_dopoln;
		}

		//std::cout << i + 1 << ")" << copu_dopoln << "\n";
		dopoln.push_back(copu_dopoln);//добовляем найденное слово
		copu_dopoln = "";
	}


	return dopoln;
}

std::vector<std::string> preposition(std::vector<std::string> text_algoritm)//алгоритм для поиска слов с предлогами
{
	std::string copy_dopoln;
	std::string copy_text;
	std::string copy;
	std::string copy_sum;
	std::vector<std::string> dopoln;

	for (int i = 0; i < text_algoritm.size(); ++i)//пробегаемся по предложениям
	{
		copy_text = text_algoritm[i];
		dopoln.push_back("");
		for (int j = 0; j < copy_text.size(); ++j)
		{
			if (copy_text[j] == ' ')// если найден нужный предлог, выводим вразу  
			{
				if (copy_dopoln == "от" || copy_dopoln == "до" || 
					copy_dopoln == "из" || copy_dopoln == "с" ||
					copy_dopoln == "у" || copy_dopoln == "без" ||
					copy_dopoln == "вокруг" || copy_dopoln == "к" ||
					copy_dopoln == "по" || copy_dopoln == "про" ||
					copy_dopoln == "через" || copy_dopoln == "в" ||
					copy_dopoln == "на" || copy_dopoln == "за" ||
					copy_dopoln == "под" || copy_dopoln == "над" ||
					copy_dopoln == "между" || copy_dopoln == "о" ||
					copy_dopoln == "об" || copy_dopoln == "при")
				{
					copy_dopoln += " ";
					for (int k = j + 1; k < copy_text.size(); ++k)
					{
						if (copy_text[k] != ' ')
						{
							copy_dopoln += copy_text[k];
						}else
						{
							//index = false;
							break;
						}
					}
					copy = copy_dopoln;
					copy_sum = ", " + copy; 
					dopoln[i] = copy_sum;//добовляем в вектор найденное дополнение
					//dopoln.push_back(copy); 
					copy = "";
				}
				copy_dopoln = "";
			}else{
				copy_dopoln += copy_text[j];
			}
		}	
	}


	return dopoln;
}

void fileInput(std::vector<std::string> text, std::vector<std::string> dop1, std::vector<std::string> dop2)//вводим в файл проанализированные данные
{
    std::ofstream file("Дополнение.txt", std::ios_base::out | std::ios_base::trunc);

    if (!file.is_open())//если файл не открылся
    {
        std::cerr << "Unable to open the file." << std::endl;
        return;
    }

    file << "\t\t\t\tПроанализированный файл:\n\n";
    file << "Разбитый текст на предложения(индекс в начеле - это номер предложения):\n";

    for (int i = 0; i < text.size(); ++i)//если нет одного алгоритма
	{
		file << i + 1 << ")" << text[i] << std::endl;
	}

	file << "\n\nВероятностные дополнения(индекс в начеле - это номер предложения, в котором найдено дополнение):\n";

	for (int i = 0; i < dop2.size(); ++i)//если все алгоритмы работают
	{
		file << i + 1 << ")" << dop1[i] << dop2[i] << std::endl;
	}
	file.close();

}

int main()
{
	std::string file;
	std::string index;
	std::string copy;
	std::vector<std::string> text;
	std::vector<std::string> dop1;
	std::vector<std::string> dop2;

    std::cout << "Здравствуйте, вы попали в программу, по вероятностному нахождению члена предложения  <Дополнение>." << std::endl;

    std::cout << "Какой текст вы хотите проанализировать:\n";
    std::cout << "1)Ввести самому.\n";
    std::cout << "2)Проанализировать текст из файла.\n\n";
    std::cout << "Ваш выбор: ";

    std::getline(std::cin, index);

    if (index == "2")
    {
    	system("clear");
	    std::cout << "Напишите название файла, который хотите проанализировать(без .txt): ";
	    std::getline(std::cin, file);
	    std::cout << "\n";

	    text = text_split(fileOut(file));
	    dop1 = last_word(text);
	    dop2 = preposition(text);

	 	fileInput(text, dop1, dop2);

	    std::cout << "Результат проанализированных данных записан в файл Дополнеие.txt в текущей директории.\n";

	    return 0;
    }else if(index == "1")
    {
    	system("clear");
    	std::cout << "Напишите ваш текст: ";

    	getline(std::cin, copy);

    	

    	text = text_split(" " + copy);
	    dop1 = last_word(text);
	    dop2 = preposition(text);

	 	fileInput(text, dop1, dop2);

	    std::cout << "\n\nРезультат проанализированных данных записан в файл Дополнеие.txt в текущей директории.\n";

	    return 0;
    }
}