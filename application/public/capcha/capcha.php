<?php
#================================================
#	Создаем надежную капчу на PHP
#
#	Автор урока:		Пакало Евгений
#	Email автора:		admin@webtyz.ru
#	Сайт урока:			http://webtyz.ru/		
#	Год написания:		2010
#================================================




// получаем путь расположение файлов (фонов,шрифтов)
// ВНИМАНИЕ В УРОКЕ ЭТО ОПИСЫВАЕТСЯ ПО ОТДЕЛЬНОСТИ, если возникли вопросы пишите в комментариях
// ЗДЕСЬ НИЧЕГО КРОМЕ ПУТИ МЕНЯТЬ НЕ НУЖНО, ДАННЫЕ ДЕЙСТВИЯ УНИВЕРСАЛЬНЫ, КАК НА ЛОКАЛЕ, ТАК И НА ХОСТИНГЕ
	$DOCUMENT_ROOT = $_SERVER["DOCUMENT_ROOT"];
	define("img_dir", "img/");
	// если капча тестируется на хостинге
		if (!empty($img_dir))
		{
			define("img_dir", $DOCUMENT_ROOT."img/"); // Путь img/ если  папка находится в корне сервера
		}

// подключаем файл конфигураций с функцией генерации кода
// установливаем пременную для config.php
$conf_const = "my_capcha";


// дополнительная проверка (не описана в уроке) если возникли вопросы, пишите в комментариях к уроку 
if (isset($conf_const) and $conf_const == "my_capcha"){
	// генерируем код капчи 
		function generate_code(){      
			// минута 
				$minuts = substr(date("i"), 0 , 1);
			// месяц     
				$mouns = date("d");
			// день в году
				$year_day = date("z"); 
			//создаем строку
				$str = $minuts . $mouns . $year_day; 
			//дважды шифруем в md5
				$str = md5(md5($str)); 
			// извлекаем 6 символов, начиная с 2
				$str = substr($str, 2, 6); 
				
			#	Вам конечно же можно постваить другие значения, 
			#	так как, если взломщики узнают, каким именно 
			#	способом это все генерируется, то в защите не будет смысла.
			
			//Тщательно все перемешиваем!!!
				$array_mix = preg_split('//', $str, -1, PREG_SPLIT_NO_EMPTY);
				srand ((float)microtime()*1000000);
				shuffle ($array_mix);
			return implode("", $array_mix);
		}
}else{
	exit("Hackers attack!");
}

// Рисуем картинку капчи
function img_code() 
{
	// говорим браузеру, что это PNG картинка 
		header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");                   
		header("Last-Modified: " . gmdate("D, d M Y H:i:s", 10000) . " GMT");
		header("Cache-Control: no-store, no-cache, must-revalidate");         
		header("Cache-Control: post-check=0, pre-check=0", false);           
		header("Pragma: no-cache");                                           
		header("Content-Type:image/png");
	// кол-во линий (может быть любым, но учтите, что введенное ниже кол-во линий будут увеличено вдвое)
		$linenum = 4; 
	// фон изображения. Можете сами нарисовать и закинутть в папку img/
		$img_arr = array(
						 "1.png",
						 "2.png",
                                                 "3.png",
                                                 "4.png"
		);
	// ttf шрифты, можно заменить на свои
		$font_arr = array(); 
			$font_arr[0]["fname"] = "addict.ttf";	// имя шрифта 
			$font_arr[0]["size"] = 20;				// размер шрифта 
		// описание еще одного шрифта, добавлять их можно сколько хотите, лишь меняйте номер в $font_arr[ ]
			$font_arr[1]["fname"] = "814yzx.ttf"; 
			$font_arr[1]["size"] = 20;
	// создаем изображение со случайным фоном
		$n = rand(0,sizeof($font_arr)-1);
		$img_fn = $img_arr[rand(0, sizeof($img_arr)-1)];
		$im = imagecreatefrompng (img_dir . $img_fn); 
	// рисуем линии
		for ($i=0; $i<$linenum; $i++)
		{
			$color = imagecolorallocate($im, rand(0, 150), rand(0, 100), rand(0, 150));
			imageline($im, rand(0, 20), rand(1, 50), rand(150, 180), rand(1, 50), $color);
		}
	$color = imagecolorallocate($im, rand(0, 200), 0, rand(0, 200));
	// накладываем код
		imagettftext ($im, $font_arr[$n]["size"], rand(-4, 4), rand(10, 45), rand(20, 35), $color, img_dir.$font_arr[$n]["fname"], generate_code());
	// еще раз линии! Уже сверху.
		for ($i=0; $i<$linenum; $i++)
		{
			$color = imagecolorallocate($im, rand(0, 255), rand(0, 200), rand(0, 255));
			imageline($im, rand(0, 20), rand(1, 50), rand(150, 180), rand(1, 50), $color);
		}
	//ну вот и создано изображение!
		ImagePNG ($im);
		ImageDestroy ($im);
}
// выводим изображение
	img_code();
?>