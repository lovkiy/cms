<?php

/**
 * Description of resize
 *
 * @author Alex
 */
class resizemodel {
   
    private static function _resize($src, $dest, $width, $height,$quality=75, $rgb=0xFFFFFF ){
    	if (!file_exists($src)){
    		return false;
    	}
    	$size = getimagesize($src);
    	if ($size === false)
    	{
    		return false;
    	}
      // Определяем исходный формат по MIME-информации, предоставленной
      // функцией getimagesize, и выбираем соответствующую формату
      // imagecreatefrom-функцию.
    	$format = strtolower(substr($size['mime'], strpos($size['mime'], '/')+1));
    	$icfunc = "imagecreatefrom" . $format;
    	
        if (!function_exists($icfunc)){
    		echo "<br />Формат выбранного Вами файла не поддерживается!<br />";
    		return false;
    	}
    	$x_ratio = $width / $size[0];
    	$y_ratio = $height / $size[1];
    
    	$ratio       = min($x_ratio, $y_ratio);
    	$use_x_ratio = ($x_ratio == $ratio);
    	$new_width   = $use_x_ratio  ? $width  : floor($size[0] * $ratio);
     	$new_height  = !$use_x_ratio ? $height : floor($size[1] * $ratio);
    	$new_left    = $use_x_ratio  ? 0 : floor(($width - $new_width) / 2);
    	$new_top     = !$use_x_ratio ? 0 : floor(($height - $new_height) / 2);
    	$isrc = $icfunc($src);
    
    	$idest = imagecreatetruecolor($width, $height);
    
    	imagefill($idest, 0, 0, $rgb);
    	imagecopyresampled($idest, $isrc, $new_left, $new_top, 0, 0, $new_width, $new_height, $size[0], $size[1]);
    	imagejpeg($idest, $dest, $quality);    	
        imagedestroy($isrc);
    	imagedestroy($idest);
    	return true;
    }
    
    static function uploadImage($file_new_name,$x,$folder,$width,$height){
    	
      	// Имя временного файла после заливки
      	$tmp = $_FILES["image"]["tmp_name"][$x];
    //	echo "<br />tmp = ".$tmp."<br />";		//  для выявления ошибок
        $name=  $_FILES["image"]["name"][$x];
    	// Проверяем, принят ли файл.
    
    	if (@file_exists($tmp)) {
    		$info = getimagesize($tmp);     
    
    		$name = "{$folder}/{$file_new_name}.jpeg";    		
         
    		// Оригинальный размер картинки
                $w =$info[0];
                $h =$info[1];
    		
                //Если картинка меньше макс. размера, то ничего не делаем
    		if (($w > $width) or ($h > $height)){
                    
                    $wmod = $width;
                    $hmod = $h / ($w / $wmod);
                    
                    if ($hmod>$height){
                        $hmod=$height;
    		        $wmod = $w / ($h / $hmod);
                    }
                }else{
                    $wmod = $w;
                    $hmod = $h;
       		}
            //Делаем уменьшенную копию поверх оригинала
         	self::_resize($tmp, $name, $wmod, $hmod);           	
           	//echo "<div class='info success'>Файл загружен.</div>";
           	return TRUE;
    	}else{
            return FALSE;
            //echo "<div class='info error'>Ошибка загрузки файла на сервер.</div>";
       	}
    }
    
}

?>
