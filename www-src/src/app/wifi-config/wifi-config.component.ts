import { Component, OnInit } from '@angular/core';
import { WifiDataSource, WifiItem } from './wifi-config-datasource';
import { DataManagerService, StatusMessage } from '../data-manager.service';

@Component({
	selector: 'app-wifi-config',
	templateUrl: './wifi-config.component.html',
	styleUrls: ['./wifi-config.component.scss'],
})
export class WifiConfigComponent implements OnInit
{
	dataSource: WifiDataSource;
	displayedColumns = ['name', 'channel', 'encrypted', 'signal', 'actions'];
	selectedWiFi: WifiItem = null;
	password: string;
	connecting: boolean = false;
	message: string;

	constructor(private data: DataManagerService)
	{
	}

	ngOnInit()
	{
		this.dataSource = new WifiDataSource(this.data);
	}

	public select(wifi: WifiItem)
	{
		this.selectedWiFi = wifi;
		this.password = '';
		if (this.selectedWiFi && !this.selectedWiFi.encrypted)
		{
			this.connect();
		}
	}

	public connect()
	{
		this.connecting = true;
		this.data.connectToWlan(this.selectedWiFi.name, this.password).subscribe(
			(status: StatusMessage) =>
			{
				if (status.code)
					this.message = status.message + ' (' + status.code + ')';
				else
				{
					this.message = 'Matrix Clock will now connect to your WiFi. It will receive new IP Address from your router.';
				}
			}
		);
	}
}
