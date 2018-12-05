import { DataSource } from '@angular/cdk/collections';
import { Observable } from 'rxjs';
import { DataManagerService } from '../data-manager.service';


export interface WifiItem {
	name: string;
	channel: number;
	encrypted: boolean;
	signal: number;
	active?: boolean;
}

export class WifiDataSource extends DataSource<WifiItem>
{
	constructor(private data: DataManagerService)
	{
		super();
	}

	connect(): Observable<WifiItem[]>
	{
		return this.data.getWlanList();
	}

	disconnect() { }
}
