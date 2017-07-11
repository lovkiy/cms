<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');
/**
 * Класс который отвечает за вывод информаци
 * на екран или вывод содержимого шаблона в
 * переменную ...
 *
 * @author Alex
 */
class Display {
    
    /*
     *Массив переменных 
     */
    
    private static $_vars = array();
    
    /*
     * Шаблон страницы по умолчанию
     */
    
    private static $_layout = 'layouts/default.tpl';
    
    private static function _set( $var, $value = '' ) {
        if( is_array( $var ) ) { // array( 'var1' => 'value1', 'var2' => 'value2' )
            $keys = array_keys( $var ) ; // array( 'var1', 'var2' )
            $values = array_values( $var ) ; // array( 'value1', 'value2' )
            self::$_vars = array_merge( self::$_vars, array_combine( $keys, $values ) ) ;
	} else {
            self::$_vars[ $var ] = $value ;
	}
    }
    
    public static function view($data=FALSE,$layout=FALSE,$type=FALSE){
        
        if(!$layout)
            $layout = self::$_layout;
        else
            $layout = $layout.EXT;
            
       if($data){
           foreach ($data as $vars => $values) {
                self::_set($vars, $values);
           }
       } 
        
              
        extract(self::$_vars, EXTR_OVERWRITE);
      
        ob_start();
        
        include APP.'templates/'.$layout;
        
        $view = ob_get_contents();        
        ob_end_clean();
      
        if($type){
            return $view;
        }else{
            echo $view;
        }            
    }
}

?>
