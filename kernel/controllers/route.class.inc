<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of route
 *TODO:Сначала нужно описать лoгику класса db  
 * @author Alex
 */
class route {
    
    public function routes($lang){
        $laguage = '';
        $request = ltrim( $_SERVER[ 'REQUEST_URI' ] ) ;
    
        if($request!=='/'):
            $this->_makeSefUrl( $request ) ;
      
            if(rtrim($lang,'/') === LANGUEGE):
                $laguage = '';               
                $request = $lang.ltrim($request,'/');                
            else:
                $laguage = $lang;
                $request = ltrim($request,'/');
            endif;
        else:
            $request = $lang.'main';
        endif;
        
        if($request==rtrim($lang,'/')):
            $request = $lang.'main';
        endif;
    
        $uri = explode('/', $request);
       
        if(!isset($uri[1])):
            errors::show_404();
        endif;
       
        $routes_default = config::$config['route_def'] ; //TODO:: реорганизовать структуру таблицы роутов...
        $routes = config::$config['route'];       
        $redirect = (config::$config['redirect'])? config::$config['redirect'] : FALSE;
        
        if($redirect):
            foreach ($redirect as $url_key=>$url_redirect):           

                if( $url_key === ltrim($request,$lang )) {
                    header( 'HTTP/1.1 301 Moved Permamently' ) ;
                    header( "Location:".BASEURL.$url_redirect ) ;
                    exit ;
                }
            endforeach;
        endif;
        
        $def = TRUE;
        if($routes):
            foreach ( $routes as $rUri => $rRoute ):
                $pattern = '`^' . $rUri. '$`u' ;

                if( preg_match( $pattern, $request ) ):
                        $route = preg_replace( $pattern, $rRoute, $request ) ;
                    $def = FALSE;    
                    break ;                
                endif; 
            endforeach;     
        endif;
        
        if($def):
            foreach ( $routes_default as $rUri => $rRoute ):
                $pattern = '`^' . $rUri. '$`u' ;
              
                if( preg_match( $pattern, $request ) ):           
                        $route = preg_replace( $pattern, $rRoute, $request );             
                    break ;                
                endif; 
            endforeach;
        endif; 
       
        $route = explode('/', $route);     
        $page = array_shift($route);  
    
       /*
        * TODO: Переписать запросс на хранимую процедуру ,для ускорения выборки
        * и кеширования в базе данных
        */
        
        if($page==='main'):
            $pages = db::GetRow("SELECT id FROM pages WHERE main=1 AND active=1"); 
        else:
            $pages = db::GetRow("SELECT id FROM pages WHERE url=".db::quote($page)." AND active=1"); 
        endif;
         
    
        if(!$pages):
            errors::show_404();
        endif;
        
        $data = array('page'=>$pages['id'],
                      'pagename'=>$page,  
                      'params'=>$route,
                      'lang'=>$laguage);
        return $data;
    }
    
    /*
     * Метод принимает URI и редиректит в случае если урл заканчивался на "/"
     */
            
    private function _makeSefUrl( $uri ) {
	$uriLen = strlen( $uri ) ;
	$lastSymbol = substr( $uri, $uriLen - 1, $uriLen ) ;
	if( $lastSymbol === '/' ) {
		header( 'HTTP/1.1 301 Moved Permamently' ) ;
		header( "Location:".rtrim($uri,'/') ) ;
		exit ;
	}
    }
}

?>
