import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { WifiItem } from './wifi-config/wifi-config-datasource';
import { HttpClient } from '@angular/common/http';
import { catchError } from 'rxjs/operators';
import { of } from 'rxjs';
import { environment } from 'src/environments/environment';


export interface StatusMessage {
	message: string;
	code?: number;
}

@Injectable({
	providedIn: 'root'
})
export class DataManagerService {

	constructor(private http: HttpClient) { }

	getWlanList(): Observable<WifiItem[]>
	{
		return this.http.get<WifiItem[]>(environment.ROOT_URL + '/wifi-scan');
	}

	connectToWlan(ssid: string, password: string): Observable<StatusMessage>
	{
		return this.http.post<StatusMessage>(environment.ROOT_URL + '/wifi-config', {ssid, password} )
		.pipe(catchError(err => of({message: err.statusText, code: err.status})));
	}
}
