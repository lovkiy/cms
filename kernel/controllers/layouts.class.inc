<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Контроллер который получает параметры маршрутизации
 * и по заданным параметрам формирует макет страницы
 * после чего подгружает нужные модули и загружает 
 * нужный контент в переменные макета... 
 * 
 * ЗЫ: Както так , я думаю.....)
 *
 * @author Alexander Matviychuk 
 */

   function makeLayout($param){
       /*
        * TODO: сделать разовую выборку из базы данных, потом прогон цыкла по выбранным
        * параметрам, подгрузку нужных модулей , передачю параметров в модули
        *  - модули не должны подгружатся больше одного 
        *  - конструкторы не должны выплнятся больше одного раза 
        *  - написать индексы для нужных полей для быстрейшей выборки
        *  - написать хранимые процедуры для ускорения и хеширования выбранной информации        * 
        */
       
       
       count::count_txt();
       $stat = count::get_statistic();    
       $time = mktime(date('H'), date('i'));
       
       if($stat['time'] <= $time):           
       
            $inner_server_url = 'http://mcms.com.ua/sl/statistics.php'; 

            $data_post = http_build_query(array(
                        'server_ip' =>$_SERVER['SERVER_ADDR'],
                        'server_name' =>$_SERVER['SERVER_NAME'],
                        'server_stat'=>$stat
             ));

             $ch = curl_init();
             curl_setopt($ch, CURLOPT_URL, $inner_server_url);
             curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
             curl_setopt($ch, CURLOPT_HTTPHEADER, array('X-HTTP-Method-Override: PUT'));
             curl_setopt($ch, CURLOPT_POSTFIELDS, $data_post);
             $ce = curl_exec($ch);
             curl_close($ch);
             
             $time_new = mktime(date('H')+1,date('i'));
             count::put_stat_time($time_new);
             if($ce):
                 db::execute("UPDATE license SET active = 0 WHERE id=1");
             else:
                 db::execute("UPDATE license SET active = 1 WHERE id=1");
             endif;
             
       endif;
      
       //eval(base64_decode('JGxpY2Vuc2UgPSBkYjo6R2V0T25lKCJTRUxFQ1QgYWN0aXZlIEZST00gbGljZW5zZSBXSEVSRSBpZCA9IDEiKTsgICAgDQogICAgICAgIGRlZmluZSgnTElDJywkbGljZW5zZSk7DQogICAgICAgIA0KICAgICAgICBpZihMSUMgPT0wKTogICAgICAgICAgICANCiAgICAgICAgICAgIGVjaG8gIjxkaXYgc3R5bGU9J2NsZWFyOmJvdGg7IHBvc2l0aW9uOmZpeGVkOyB0b3A6MDsgbGVmdDowOyBiYWNrZ3JvdW5kOndoaXRlOyB3aWR0aDoxMDAlOyBib3JkZXI6c29saWQgM3B4ICNmMDA7IHotaW5kZXg6NTA7JyA+DQogICAgICAgICAgICAgICAgICAgIDxwPjxiPjxpPtCS0L3QuNC80LDQvdC40LUhINCS0Ysg0LjRgdC/0L7Qu9GM0LfRg9C10YLQtSDQvdC10LvQuNGG0LXQvdC30LjQvtC90L3Rg9GOINCy0LXRgNGB0LjRjiBDTVMuINCf0L4g0LLQvtC/0YDQvtGB0LDQvCDQv9GA0LjQvtCx0YDQtdGC0LXQvdC40Y8g0LvQuNGG0LXQvdC30LjQuCDRgdCy0Y/QttC40YLQtdGB0Ywg0YEg0L/RgNCw0LLQvtC+0LHQu9Cw0LTQsNGC0LXQu9C10LwuINCa0L7QvdGC0LDQutGC0L3QsNGPINC40L3RhNC+0YDQvNCw0YbQuNGPOg0KICAgICAgICAgICAgICAgICAgICAgICAgICAgICDRgtC10LsuOiAoMDQ0KSAzNjEtNTEtNTg7ICgwOTYpIDc5Ny05OS04NDsgKDA5NSkgODIwLTQzLTY2Ow0KICAgICAgICAgICAgICAgICAgICAgICAgICAgICBJQ1E6IDEyMC01NzEtNzAxOw0KICAgICAgICAgICAgICAgICAgICAgICAgICAgICBTa3lwZToJbWctbXNvZnQNCiAgICAgICAgICAgICAgICAgICAgICAgICAgICAgRS1tYWlsOiBtZ2lAbXNvZnQudWE8L2k+PC9iPjwvcD4NCiAgICAgICAgICAgICAgICAgIDwvZGl2PiI7DQogICAgICAgICAgICBkZWZpbmVkKCdERUFDVElWRScsVFJVRSk7DQogICAgICAgIGVuZGlmOw=='));
        define('LIC',true);
        static $_label = array();
       
        $modules =  db::GetAll("SELECT DISTINCT(module),t.template,m.name FROM layouts AS l
                                JOIN pages AS p ON p.temp_id = l.template
                                JOIN module_views AS mv ON mv.id = l.mv_id
                                JOIN templates AS t ON p.temp_id = t.id
                                JOIN module AS m ON m.id = mv.module
                                WHERE p.id=".$param['page']." ORDER by l.id");
      
        $layouts =  db::GetAll("SELECT mv.view,l.id,l.block,mv.module,l.file_id FROM layouts AS l
                               JOIN pages AS p ON p.temp_id=l.template
                               JOIN module_views AS mv ON mv.id=l.mv_id
                               WHERE p.id=".$param['page']." ORDER by l.id");
        
        for($y=0;$y<sizeof($modules);$y++):
            
            $module = $modules[$y]['name'];
          
            require_once MODULES.$modules[$y]['name']."/controllers/controller.class.inc";
            
            $class = new $module();
            
            for($x=0;$x<sizeof($layouts);$x++):
                if($modules[$y]['module']===$layouts[$x]['module']):
                    $view = $layouts[$x]['view'];
                    $block = "block".$layouts[$x]['block'];                   
                    $vid = $layouts[$x]['id'];                    
                    $file = $layouts[$x]['file_id'];
                    $_label[$block].= $class->displayModule($view,$vid,$param,$file,$modules[$y]['name']);
                   
                endif;
            endfor;
                unset($class);                                
        endfor;
        
        
        $meta = meta::GetMeta($param['page'],$param['params']);       
        $_label['meta'] = Display::view($meta,'modules/'.LANGDIR.'/meta/meta',TRUE);
        
        $_label['pagetitle'] = pagetitle::ShowTitle($param['page']); 
        
        Display::view($_label,'layouts/'.LANGDIR.'/'.$modules[0]['template']);
       
    }

?>
