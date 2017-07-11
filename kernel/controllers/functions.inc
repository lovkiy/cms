<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of languages
 *
 * @author Alex
 */

require_once CORE.'controllers/display.class.inc';
require_once CORE.'controllers/errors.class.inc';
require_once CORE.'controllers/db.class.inc';
require_once CORE.'controllers/meta.class.inc';
require_once CORE.'controllers/pagetitle.class.inc';
require_once CORE.'controllers/mail.class.inc';
require_once CORE.'controllers/capcha.class.inc';
require_once CORE.'controllers/count.class.inc';

function rus2translit($string) {
    $converter = array(
        'а' => 'a','б' => 'b','в' => 'v','г' => 'g','д' => 'd','е' => 'e',
        'ё' => 'e','ж' => 'zh','з' => 'z','и' => 'i','й' => 'y','к' => 'k',
        'л' => 'l','м' => 'm','н' => 'n','о' => 'o','п' => 'p','р' => 'r',
        'с' => 's','т' => 't','у' => 'u','ф' => 'f','х' => 'h','ц' => 'c',
        'ч' => 'ch','ш' => 'sh','щ' => 'sch','ь' => '\'','ы' => 'y','ъ' => '\'',
        'э' => 'e','ю' => 'yu','я' => 'ya',

        'А' => 'A','Б' => 'B','В' => 'V','Г' => 'G','Д' => 'D','Е' => 'E',
        'Ё' => 'E','Ж' => 'Zh','З' => 'Z','И' => 'I','Й' => 'Y','К' => 'K',
        'Л' => 'L','М' => 'M','Н' => 'N','О' => 'O','П' => 'P','Р' => 'R',
        'С' => 'S','Т' => 'T','У' => 'U','Ф' => 'F','Х' => 'H','Ц' => 'C',
        'Ч' => 'Ch','Ш' => 'Sh','Щ' => 'Sch','Ь' => '\'','Ы' => 'Y','Ъ' => '\'',
        'Э' => 'E','Ю' => 'Yu','Я' => 'Ya',
    );
    return strtr($string, $converter);
}

function toAscii($str, $replace=array(), $delimiter='-') {
    if( !empty($replace) ) {
        $str = str_replace((array)$replace, ' ', $str);
    }

    $clean = iconv('UTF-8', 'ASCII//TRANSLIT', $str);
    $clean = preg_replace("/[^a-zA-Z0-9\/_|+ -]/", '', $clean);
    $clean = strtolower(trim($clean, '-'));
    $clean = preg_replace("/[\/_|+ -]+/", $delimiter, $clean);

    return $clean;
}

function setLanguege($langarray){
    
    $lang = LANGUEGE.'/';    
    
    $uri = explode('/', ltrim( $_SERVER[ 'REQUEST_URI' ] ));
    $languege = $uri[1];
  
    if($languege):
        if(in_array($languege, $langarray)):         
            $lang = $languege.'/';        
        endif;        
    endif;    
    
    return $lang;
}

function __autoload($class){
    require_once CORE.'controllers/'.$class.'.class.inc';    
 }
require_once CORE.'controllers/layouts.class.inc';
?>
