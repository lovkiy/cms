<?php

/**
 * Description of capcha
 *
 * @author Alex
 */
class capcha {
   private static function generate_code(){      
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
    
    public static function chec_code($code){
        //удаляем пробелы
	$code = trim($code);
        
        $array_mix = preg_split ('//', self::generate_code(), -1, PREG_SPLIT_NO_EMPTY);
	$m_code = preg_split ('//', $code, -1, PREG_SPLIT_NO_EMPTY);

	$result = array_intersect ($array_mix, $m_code);
	if (strlen(self::generate_code())!=strlen($code)){return FALSE;}
	if (sizeof($result) == sizeof($array_mix)){return TRUE;}else{return FALSE;}
    }    
}

?>
