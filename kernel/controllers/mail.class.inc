<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of mailmodel
 *
 * @author Alex
 */
class mail {
    
    public static function sendMail($to, $subj, $from, $message){
            
            	$charset = 'utf8';//кодировка письма
            	$subj = self::subj_encode($subj, $charset);//кодируем поле "Тема"
            	$header = "MIME-Version: 1.0\r\n";
            	$header .= "X-Mailer: PHPMail Tool\r\n";
            	$head .= "X-Sender: $from\r\n";
            	$header .= "X-Priority: 3\r\n";//приоритет
            	
            
                $boundary="------"; /* задать разделитель файлов */
                $header.="From: $from\n"; 
                $header.="Content-Type: multipart/mixed; boundary=\"$boundary\""; 
                $body=""; 
                $body.="--$boundary\n";
                $body .= "Content-Type: text/html; charset=$charset\r\n";
                $body .= "$message\r\n";
               
                //Перечисляем все загруженые файлы и создаем для каждого отдельный Header.........
                
                for ($i=0; $i < sizeof($_FILES['upload']['tmp_name']); $i++) 
                {
                  $body.= self::attach($_FILES['upload']['tmp_name'][$i],$_FILES['upload']['name'][$i],$boundary); /* для каждого элемента массива (каждого файла) вызвать функцию обработки */
                }
                    
                
                $body.="--".$boundary ."--\n"; /* добавление двух дефисов ДО и ПОСЛЕ для закрывающего разделителя ОБЯЗАТЕЛЬНО! */
                
            
            	 if(mail($to, $subj, $body, $header)){
            	   return TRUE;
                   
            	 }else{
            	   return FALSE;
            	 }
        }
    
       private static function attach($tmp_name,$name,$boundary) { /* функция обработает каждый файл */
            
              //GLOBAL $boundary; /* определить что, эти переменные берутся из глобальных (ранее определенных), а не создаются локально (фишка PHP) */
              @$file=fopen($tmp_name,"rb"); /* открыть файл */
             
              $text=fread($file, filesize($tmp_name)); /* считать весь в переменную */
              fclose($file); /* закрыть */
              $body.="--$boundary\n"; /* добавление двух дефисов ОБЯЗАТЕЛЬНО! */
              $body.="Content-Type: application/octet-stream; name==?windows-1251?B?". base64_encode($name). "?=\r\n"; 
              $body.="Content-Transfer-Encoding: base64\r\n";
              $body.="Content-Disposition: attachment; filename==?windows-1251?B?". base64_encode($name). "?=\r\n\n"; 
              $body.=chunk_split(base64_encode($text))."\n"; /* закодировать полученное из файла и добавить в тело письма */
            
            return $body;
      }
      //Функциия кодирует тему письма ......................
      private static function subj_encode($str, $data_charset, $send_charset=false){
            
        	# Если задана кодировка передачи и она не совпадает
        	# с кодировкой данных, конвертируем строку
        	if($send_charset AND $data_charset!=$send_charset)
        		$str = iconv($data_charset, $send_charset, $str);
        	else
        		$send_charset = $data_charset;
        	return '=?'.$send_charset.'?B?'.base64_encode($str).'?=';
      }
}

?>
