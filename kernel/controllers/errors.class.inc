<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Класс обработки ошибок 
 * TODO: Добавить обраотку ошибок браузера
 * 500 503 - и также возможность редактирования 
 * шаблона данных ошибок...
 * добавить оформление остальных ошибок...
 * @author Alex
 */
class errors {

    /*
     * Перехватывает ошибки которые возможно обработать
     * NOTICE , WARNINGS
     */
    
    public static function captureNormal( $number, $message, $file, $line ){        
        
        // Выводим содержимое массива ошибок 
       if(DEBBUG) 
        echo"<table  border='1' cellspacing='1' style='background-color: #BFE9FD;'  >
                <tr>
                    <th>Номер</th>
                    <th>Строка</th>
                    <th>Фаил</th>
                    <th>Описание</th>
                </tr>
                     <td>$number</td>
                     <td><b>$line</b></td>
                     <td>$file</td>                     
                     <td><b>$message</b></td>
            </table>";
    }
   
    /*
     *Перехватывает ошбки связаные с исключениями
     *  
     */
    
    public static function captureException( $exception ){
        
        echo '<pre>';
        print_r( $exception );
        echo '</pre>';
    }
   
    /*
     * Обрабатывает ошибки которые невозможно 
     * перехватить FATAL ERORR
     */
    public static function captureShutdown( ){
       
        $error = error_get_last( );
        if( $error ) {
            // Нужно закоментировать если хотим видеть что выводилось до ошибки
           // ob_end_clean( );           
           
            echo '<pre>';
            print_r( $error );
            echo '</pre>';
        } else { return true; }
    }
    
    /*
     *Показывает страницу 404 с привильными
     * заголовками... 
     */
    
    public static function show_404(){
       // ob_end_clean( );
        header('HTTP/1.1 404 Not Found');
	header("Status: 404 Not Found");
        $error = Display::view('','errors/'.LANGDIR.'/error404',TRUE);
        exit($error);  
    }
}

/*
 *Функции нужные для отладки перехватчика ошибок...
 * 
 * 

PHP set_error_handler TEST
IMAGINE_CONSTANT;

 PHP set_exception_handler TEST
throw new Exception( 'Imagine Exception' );

 PHP register_shutdown_function TEST ( IF YOU WANT TEST THIS, DELETE PREVIOUS LINE )
imagine_function( );
*/